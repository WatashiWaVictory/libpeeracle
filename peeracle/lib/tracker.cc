#include <sys/syslog.h>
#include <cstring>
#include <iostream>
#include "webrtc/base/json.h"
#include "third_party/libwebsockets/lib/libwebsockets.h"
#include "peeracle/lib/tracker.h"
#include "peeracle/lib/trackerobserverinterface.h"
#include "trackerannounceobserverinterface.h"

namespace peeracle {

static int callback(struct libwebsocket_context *context,
  struct libwebsocket *wsi, enum libwebsocket_callback_reasons reason,
  void *user, void *in, size_t len) {
  Tracker *tracker = (Tracker *) user;

  switch (reason) {
    case LWS_CALLBACK_CLOSED:
    case LWS_CALLBACK_CLOSED_HTTP:
    case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
      lwsl_notice("Client has disconnected\n");
      if (tracker->getObserver()) {
        tracker->getObserver()->OnDisconnect();
      }
      break;
    case LWS_CALLBACK_CLIENT_ESTABLISHED:
      lwsl_notice("Client has connected\n");
      tracker->SendHello();
      break;
    case LWS_CALLBACK_CLIENT_RECEIVE:
      tracker->OnReceive(in, len);
      break;
    case LWS_CALLBACK_CLIENT_WRITEABLE:
      tracker->ProcessQueue();
      break;
    default:
      break;
  }
  return 0;
}

static struct libwebsocket_protocols protocols[] = {
  {
    "peeracle",                  /* name */
    callback,                    /* callback */
    sizeof(Tracker *)            /* per_session_data_size */
  },
  {
    NULL, NULL, 0    /* End of list */
  }
};

Tracker::Tracker()
  : tracker_observer_(NULL),
    context_(NULL),
    wsi_(NULL),
    state_(0),
    callrate_
    (250000),
    lastcall_(0) {
  messagehandlers_["welcome"] = &Tracker::HandleWelcome_;
  messagehandlers_["announce"] = &Tracker::HandleAnnounce_;
  messagehandlers_["signal"] = &Tracker::HandleSignal_;
  messagehandlers_["quit"] = &Tracker::HandleQuit_;
}

Tracker::~Tracker() {
  libwebsocket_context_destroy(context_);
}

bool Tracker::Initialize(TrackerObserverInterface *observer) {
  int use_ssl = 0;
  struct lws_context_creation_info info;

  tracker_observer_ = observer;

#ifdef WIN32
#else
  int syslog_options = LOG_PID | LOG_PERROR;
  int debug_level = 7;
  /* we will only try to log things according to our debug_level */
  setlogmask(LOG_UPTO(LOG_DEBUG));
  openlog("lwsts", syslog_options, LOG_DAEMON);

  /* tell the library what debug level to emit and to send it to syslog */
  lws_set_log_level(debug_level, lwsl_emit_syslog);
#endif

  memset(&info, 0, sizeof(info));
  info.port = CONTEXT_PORT_NO_LISTEN;
  info.iface = NULL;
  info.protocols = protocols;
  info.extensions = libwebsocket_get_internal_extensions();
  info.ssl_ca_filepath = NULL;
  info.ssl_cert_filepath = NULL;
  info.ssl_private_key_filepath = NULL;
  info.ssl_private_key_password = NULL;
  info.gid = -1;
  info.uid = -1;
  info.options = 0;

  context_ = libwebsocket_create_context(&info);
  if (context_ == NULL) {
    lwsl_err("libwebsocket init failed\n");
    return false;
  }

  lwsl_notice("Client connecting to %s:%u...\n", "127.0.0.1", 8080);
  wsi_ = libwebsocket_client_connect_extended(context_, "127.0.0.1",
    8080, use_ssl, "/", "127.0.0.1:8080",
    "origin", NULL, -1, this);
  if (!wsi_) {
    lwsl_err("Client failed to connect\n");
    return false;
  }

  state_ = 1;
  return true;
}

bool Tracker::Update() {
  struct timeval tv;

  if (state_ < 1) {
    return false;
  }

  if (!queue_.empty()) {
    gettimeofday(&tv, NULL);
    if (((unsigned int) tv.tv_usec - lastcall_) > callrate_) {
      libwebsocket_callback_on_writable_all_protocol(&protocols[0]);
      lastcall_ = tv.tv_usec;
    }
  }

  return libwebsocket_service(context_, 0) >= 0;
}

void Tracker::Terminate() {
  state_ = -1;
}

bool Tracker::Announce(const std::string &hash, const std::string &got,
  TrackerAnnounceObserverInterface *announceObserver) {
  Json::FastWriter writer;
  Json::Value jmessage;

  jmessage["type"] = "announce";
  jmessage["hash"] = hash;
  jmessage["got"] = got;

  Send_(writer.write(jmessage));

  if (announces_.find(hash) != announces_.end()) {
    lwsl_err("hash is already defined!\n");
    return false;
  }

  announces_[hash] = announceObserver;
  return true;
}

bool Tracker::SendSessionDescription(const std::string& peer,
  const std::string& hash, const std::string& sdp) {
  Json::Reader reader;
  Json::FastWriter writer;
  Json::Value jmessage;
  Json::Value jsdp;

  jmessage["type"] = "signal";
  jmessage["sign"] = "sdp";
  jmessage["peer"] = peer;
  jmessage["hash"] = hash;

  if (!reader.parse(sdp, jsdp)) {
    return false;
  }
  jmessage["data"] = jsdp;

  Send_(writer.write(jmessage));
  return true;
}

bool Tracker::SendIceCandidate(const std::string& peer,
  const std::string& hash, const std::string& ice) {
  Json::Reader reader;
  Json::FastWriter writer;
  Json::Value jmessage;
  Json::Value jice;

  jmessage["type"] = "signal";
  jmessage["sign"] = "ice";
  jmessage["peer"] = peer;
  jmessage["hash"] = hash;

  if (!reader.parse(ice, jice)) {
    return false;
  }
  jmessage["data"] = jice;

  Send_(writer.write(jmessage));
  return true;
}

TrackerObserverInterface* Tracker::getObserver() {
  return tracker_observer_;
}

void Tracker::OnReceive(void *data, size_t length) {
  Json::Reader reader;
  Json::Value jmessage;

  lwsl_notice("Client RX: %s (%u)", (char *) data, length);
  if (!reader.parse((char *) data, jmessage)) {
    lwsl_err("ERROR received unknown message\n");
    return;
  }

  std::string type;
  if (!GetStringFromJsonObject(jmessage, "type", &type)) {
    lwsl_err("ERROR message has no type key\n");
    return;
  }

  lwsl_notice("Message type : %s\n", type.c_str());
  if (messagehandlers_.find(type) == messagehandlers_.end()) {
    return;
    lwsl_err("type : %s is unknown\n", type.c_str());
  }

  MessageHandler mh = messagehandlers_[type];
  (this->*mh)(jmessage);
}

void Tracker::SendHello() {
  Json::FastWriter writer;
  Json::Value jmessage;

  jmessage["type"] = "hello";

  Send_(writer.write(jmessage));
}

void Tracker::ProcessQueue() {
  int n;
  size_t len;
  unsigned char data[LWS_SEND_BUFFER_PRE_PADDING + 1400 +
    LWS_SEND_BUFFER_POST_PADDING];
  std::string buffer;

  if (queue_.empty()) {
    return;
  }

  buffer = queue_.top();
  len = (size_t) sprintf((char *) &data[LWS_SEND_BUFFER_PRE_PADDING],
    buffer.c_str());
  lwsl_notice("Client TX: %s", &data[LWS_SEND_BUFFER_PRE_PADDING]);
  n = libwebsocket_write(wsi_, &data[LWS_SEND_BUFFER_PRE_PADDING],
    len, LWS_WRITE_TEXT);
  if (n < 0) {
    lwsl_err("ERROR %d writing to socket, hanging up\n", n);
    return;
  }
  if (n < (int) len) {
    lwsl_err("Partial write\n");
    return;
  }
  queue_.pop();
  libwebsocket_callback_on_writable_all_protocol(&protocols[0]);
}

void Tracker::Send_(const std::string &buffer) {
  queue_.push(buffer);
  libwebsocket_callback_on_writable_all_protocol(&protocols[0]);
}

void Tracker::HandleWelcome_(const Json::Value &jmessage) {
  lwsl_notice("Got welcome message\n");
  if (tracker_observer_) {
    tracker_observer_->OnConnect();
  }
}

void Tracker::HandleAnnounce_(const Json::Value &jmessage) {
  lwsl_notice("Got announce message\n");

  std::string hash;
  if (!GetStringFromJsonObject(jmessage, "hash", &hash)) {
    lwsl_err("ERROR message has no hash key\n");
    return;
  }

  if (announces_.find(hash) == announces_.end()) {
    lwsl_err("hash not found!\n");
    return;
  }
  TrackerAnnounceObserverInterface *observer = announces_[hash];

  std::vector<Json::Value> peers;
  JsonArrayToValueVector(jmessage["peers"], &peers);

  for (std::vector<Json::Value>::iterator it = peers.begin(); it != peers.end
    (); it++) {
    std::string id;
    if (!GetStringFromJsonObject((*it), "id", &id)) {
      lwsl_err("id not found!\n");
      return;
    }

    std::string got;
    if (!GetStringFromJsonObject((*it), "got", &got)) {
      lwsl_err("got not found!\n");
      return;
    }

    observer->OnPeerConnect(id, got);
  }
}

void Tracker::HandleSignal_(const Json::Value &jmessage) {
  lwsl_notice("Got signal message\n");

  std::string hash;
  if (!GetStringFromJsonObject(jmessage, "hash", &hash)) {
    lwsl_err("ERROR message has no hash key\n");
    return;
  }

  if (announces_.find(hash) == announces_.end()) {
    lwsl_err("hash not found!\n");
    return;
  }

  TrackerAnnounceObserverInterface *observer = announces_[hash];

  std::string sign;
  if (!GetStringFromJsonObject(jmessage, "sign", &sign)) {
    lwsl_err("ERROR message has no sign key\n");
    return;
  }

  if (sign != "ice" && sign != "sdp") {
    lwsl_err("ERROR invalid signal type\n");
    return;
  }

  std::string peer;
  if (!GetStringFromJsonObject(jmessage, "peer", &peer)) {
    lwsl_err("ERROR message has no peer key\n");
    return;
  }

  std::string data = JsonValueToString(jmessage["data"]);
  lwsl_notice("data = %s\n", data.c_str());

  if (sign == "ice") {
    lwsl_notice("Got Ice candidate\n");
    observer->OnIceCandidate(peer, data);
  } else if (sign == "sdp") {
    lwsl_notice("Got Session description\n");

    Json::Reader reader;
    Json::Value jsdp;

    if (!reader.parse(data, jsdp)) {
      lwsl_err("ERROR can't parse data\n");
      return;
    }

    std::string type;
    if (!GetStringFromJsonObject(jsdp, "type", &type)) {
      lwsl_err("ERROR message has no type key\n");
      return;
    }

    if (type == "offer") {
      lwsl_notice("Got OFFER !\n");
      observer->OnOffer(peer, data);
    } else if (type == "answer") {
      lwsl_notice("Got ANSWER !\n");
      observer->OnAnswer(peer, data);
    }
  }
}

void Tracker::HandleQuit_(const Json::Value &jmessage) {
  lwsl_notice("Got quit message\n");
  std::string id;
  if (!GetStringFromJsonObject(jmessage, "id", &id)) {
    lwsl_err("ERROR message has no id key\n");
    return;
  }
}

}
