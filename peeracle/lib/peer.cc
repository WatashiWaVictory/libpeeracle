#include <talk/app/webrtc/mediaconstraintsinterface.h>
#include "third_party/jsoncpp/source/include/json/reader.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "webrtc/base/json.h"
#include "webrtc/base/logging.h"
#include "peercreatesessiondescriptionobserver.h"
#include "peerconnectionobserver.h"
#include "peer.h"

namespace peeracle {

Peer::Peer() {
  mediaconstraints_.SetAllowDtlsSctpDataChannels();
}

Peer::~Peer() {
}

bool Peer::Initialize(PeerObserverInterface* observer) {
  peer_observer_ = observer;

  rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface>
    peer_connection_factory = webrtc::CreatePeerConnectionFactory();

  if (!peer_connection_factory.get()) {
    LOG(LS_ERROR) << "Failed to initialize PeerConnectionFactory";
    return false;
  }

  webrtc::PeerConnectionInterface::IceServers servers;
  webrtc::PeerConnectionInterface::IceServer server;
  server.uri = "stun:stun.l.google.com:19302";

  servers.push_back(server);

  peer_connection_observer_ = new PeerConnectionObserver(peer_observer_);
  peer_connection_ = peer_connection_factory->CreatePeerConnection(servers,
    &mediaconstraints_,
    NULL,
    NULL,
    peer_connection_observer_);

  if (!peer_connection_.get()) {
    LOG(LS_ERROR) << "Failed to call CreatePeerConnection";
    return false;
  }

  peer_connection_observer_->SetPeerConnection(peer_connection_);
  return true;
}

void Peer::Terminate() {

}

void Peer::CreateOffer(PeerCreateSessionDescriptionObserverInterface*
  observer) {
  webrtc::DataChannelInit init;
  init.ordered = true;

  data_channel_ = peer_connection_->CreateDataChannel("data", &init);
  signal_channel_ = peer_connection_->CreateDataChannel("signal", &init);

  peer_connection_->CreateOffer(observer, &mediaconstraints_);
}

void Peer::CreateAnswer(PeerCreateSessionDescriptionObserverInterface*
  observer) {
  peer_connection_->CreateAnswer(observer, &mediaconstraints_);
}

void Peer::SetLocalDescription(PeerSetSessionDescriptionObserverInterface *observer,
  const std::string &jobject) {
  Json::Reader reader;
  Json::Value jdesc;
  webrtc::SessionDescriptionInterface *desc;

  if (!reader.parse(jobject, jdesc)) {
    LOG(WARNING) << "Unknown string desc " << jobject;
    return;
  }

  std::string type;
  GetStringFromJsonObject(jdesc, "type", &type);

  std::string sdp;
  GetStringFromJsonObject(jdesc, "sdp", &sdp);

  desc = webrtc::CreateSessionDescription(type, sdp);

  peer_connection_->SetLocalDescription(new
    rtc::RefCountedObject<PeerSetSessionDescriptionObserver>(observer), desc);
}

void Peer::SetRemoteDescription(PeerSetSessionDescriptionObserverInterface *observer,
  const std::string &jobject) {
  Json::Reader reader;
  Json::Value jdesc;
  webrtc::SessionDescriptionInterface *desc;

  if (!reader.parse(jobject, jdesc)) {
    LOG(WARNING) << "Unknown string desc " << jobject;
    return;
  }

  std::string type;
  GetStringFromJsonObject(jdesc, "type", &type);

  std::string sdp;
  GetStringFromJsonObject(jdesc, "sdp", &sdp);

  desc = webrtc::CreateSessionDescription(type, sdp);

  peer_connection_->SetRemoteDescription(new
    rtc::RefCountedObject<PeerSetSessionDescriptionObserver>(observer), desc);
}

void Peer::AddICECandidate(const std::string &jobject) {
  std::string sdp_mid;
  int sdp_mlineindex = 0;
  std::string sdp;
  Json::Reader reader;
  Json::Value jdesc;

  reader.parse(jobject, jdesc);
  if (!GetStringFromJsonObject(jdesc, "sdpMid", &sdp_mid) ||
    !GetIntFromJsonObject(jdesc, "sdpMLineIndex",
      &sdp_mlineindex) ||
    !GetStringFromJsonObject(jdesc, "candidate", &sdp)) {
    LOG(WARNING) << "Can't parse received message.";
    return;
  }
  rtc::scoped_ptr<webrtc::IceCandidateInterface> candidate(
    webrtc::CreateIceCandidate(sdp_mid, sdp_mlineindex, sdp));
  if (!candidate.get()) {
    LOG(WARNING) << "Can't parse received candidate message.";
    return;
  }

  peer_connection_->AddIceCandidate(candidate.get());
}

PeerObserverInterface* Peer::getObserver() const {
  return peer_observer_;
}

PeerConnectionObserverInterface *Peer::getConnectionObserver() const {
  return peer_connection_observer_;
}

}
