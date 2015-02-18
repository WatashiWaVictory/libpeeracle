#include "peeracle.h"

#include <iostream>
#include <cstring>
#include <map>

#include "peeracle/lib/manager.h"

#include "peeracle/lib/peerfactory.h"
#include "peeracle/lib/peerinterface.h"
#include "peeracle/lib/peerobserverinterface.h"
#include "peeracle/lib/peersetsessiondescriptionobserverinterface.h"

#include "peeracle/lib/trackerinterface.h"
#include "peeracle/lib/trackerfactory.h"
#include "peeracle/lib/trackerobserverinterface.h"
#include "peeracle/lib/trackerannounceobserverinterface.h"

#define PEERACLE_SAMPLE_HASH "4d5236eba999a8ad85e19c5fac1ce6a929f093d99e4071ded8024fee14e80c66cd156966fc12280746bf9cfe75ec1267c906db23c7d20e6e0ebe0e20b6c62f03"
#define PEERACLE_SAMPLE_GOT "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"

std::map<std::string, peeracle::PeerInterface*> peers;

class MyPeerSetSessionDescriptionObserver
  : public peeracle::PeerSetSessionDescriptionObserverInterface {
 public:
  MyPeerSetSessionDescriptionObserver() {}

  void OnSuccess() {
    std::cout << std::endl <<
      "[MyPeerSetSessionDescriptionObserver::OnSuccess]" << std::endl <<
      std::endl;
  }

  void OnFailure(const std::string& error) {
    std::cout << "[MyPeerSetSessionDescriptionObserver::OnFailure] " <<
      error << std::endl <<
      std::endl;
  }

 protected:
  ~MyPeerSetSessionDescriptionObserver() {}
};

class MyPeerObserver
  : public peeracle::PeerObserverInterface {
 public:
  MyPeerObserver(peeracle::PeerInterface* peer,
    const std::string& id, const std::string& hash,
    peeracle::TrackerInterface *tracker)
    : peer_(peer),
      id_ (id),
      hash_(hash),
      tracker_(tracker) {}

  void OnIceCandidate(const std::string& jobject) {
    std::cout << "[MyPeerObserver::OnIceCandidate]" << std::endl;

    tracker_->SendIceCandidate(id_, hash_, jobject);
  }

  void OnSessionDescription(const std::string& jobject){
    std::cout << "[MyPeerObserver::OnSessionDescription]" << std::endl;

    peeracle::PeerSetSessionDescriptionObserverInterface*
      setDescriptionObserver =
      new MyPeerSetSessionDescriptionObserver();
    peer_->SetLocalDescription(setDescriptionObserver, jobject);
    tracker_->SendSessionDescription(id_, hash_, jobject);
  }

 private:
  peeracle::PeerInterface *peer_;
  const std::string id_;
  const std::string hash_;
  peeracle::TrackerInterface *tracker_;

 protected:
  ~MyPeerObserver() {}
};

class MyTrackerAnnounceObserver
  : public peeracle::TrackerAnnounceObserverInterface {
 public:
  MyTrackerAnnounceObserver(peeracle::TrackerInterface *tracker,
    const std::string& hash) : tracker_(tracker),
                               hash_(hash) {}

  void OnPeerConnect(const std::string& id, const std::string& got) {
    std::cout << "[tracker] Peer connected " << id << std::endl;

    peeracle::PeerInterface* p = peeracle::PeerFactory::Create();
    MyPeerObserver *peerObserver = new MyPeerObserver(p, id, hash_, tracker_);
    peers[id] = p;

    p->Initialize(peerObserver);
    p->CreateOffer();
  }

  void OnPeerDisconnect(const std::string& id) {
    std::cout << "[tracker] Peer disconnected " << id << std::endl;
  }

  void OnOffer(const std::string& id, const std::string& sdp) {
    std::cout << "[tracker] Got offer session description " << std::endl;

    if (peers.find(id) == peers.end()) {
      std::cout << "[tracker] peer not found" << std::endl;

      peeracle::PeerInterface* p = peeracle::PeerFactory::Create();
      MyPeerObserver *peerObserver = new MyPeerObserver(p, id, hash_, tracker_);
      peers[id] = p;

      peers[id]->Initialize(peerObserver);
    }

    peeracle::PeerSetSessionDescriptionObserverInterface*
      setDescriptionObserver = new MyPeerSetSessionDescriptionObserver();
    peers[id]->SetRemoteDescription(setDescriptionObserver, sdp);
    peers[id]->CreateAnswer();
  }

  void OnAnswer(const std::string& id, const std::string& sdp) {
    std::cout << "[MyTrackerAnnounceObserver::OnAnswer]" << std::endl;

    if (peers.find(id) == peers.end()) {
      std::cout << "[tracker] peer not found" << std::endl;
      return;
    }

    peeracle::PeerSetSessionDescriptionObserverInterface*
      setDescriptionObserver =
      new MyPeerSetSessionDescriptionObserver();
    peers[id]->SetRemoteDescription(setDescriptionObserver, sdp);
  }

  void OnIceCandidate(const std::string& id, const std::string& ice) {
    std::cout << "[MyTrackerAnnounceObserver::OnIceCandidate]" << std::endl;

    if (peers.find(id) == peers.end()) {
      std::cout << "[tracker] peer not found" << std::endl;
    }

    peers[id]->AddICECandidate(ice);
  }

 private:
  peeracle::TrackerInterface *tracker_;
  const std::string hash_;

 protected:
  ~MyTrackerAnnounceObserver() {}
};

class MyTrackerObserver
  : public peeracle::TrackerObserverInterface {
 public:
  MyTrackerObserver(peeracle::TrackerInterface *tracker) : tracker_(tracker) {}

  void OnConnect() {
    std::cout << "[MyTrackerObserver::OnConnect]" << std::endl;
    tracker_->Announce
      (PEERACLE_SAMPLE_HASH,
        PEERACLE_SAMPLE_GOT,
        new MyTrackerAnnounceObserver(tracker_, PEERACLE_SAMPLE_HASH));
  }
  void OnDisconnect(){
    std::cout << "[MyTrackerObserver::OnDisconnect]" << std::endl;
  }

 private:
  peeracle::TrackerInterface *tracker_;

 protected:
  ~MyTrackerObserver() {}
};

struct access_sys_t
{
  peeracle::TrackerInterface *tracker;
  peeracle::TrackerObserverInterface *trackerObserver;
};

static int AccessControl( access_t *p_access, int i_query, va_list args );
static ssize_t AccessRead( access_t *p_access, uint8_t *p_buffer, size_t sz );
static int AccessSeek( access_t *p_access, uint64_t seek_len );

int AccessOpen(vlc_object_t *p_this)
{
  access_t *p_access = (access_t*)p_this;
  access_sys_t *p_sys;

  msg_Info(p_access, "Hello from peeracle access!");

  if (!strstr(p_access->psz_filepath, ".peeracle")) {
    return VLC_EGENERIC;
  }

  p_access->p_sys = p_sys = (access_sys_t*)calloc( 1, sizeof( *p_sys ) );
  if( !p_sys )
    return VLC_ENOMEM;

  ACCESS_SET_CALLBACKS( AccessRead, NULL, AccessControl, AccessSeek );

  //new peeracle::Manager;
  p_sys->tracker = peeracle::TrackerFactory::Create();
  p_sys->trackerObserver = new MyTrackerObserver(p_sys->tracker);
  p_sys->tracker->Initialize(p_sys->trackerObserver);

  return VLC_SUCCESS;
}

void AccessClose( vlc_object_t *p_this )
{
  access_t *p_access = (access_t*)p_this;
  access_sys_t *p_sys = p_access->p_sys;

  msg_Info(p_access, "Goodbye from peeracle access!");
  free(p_sys);
}

static int AccessControl( access_t *p_access, int i_query, va_list args )
{
  msg_Info(p_access, "AccessControl!");
  return VLC_SUCCESS;
}

static ssize_t AccessRead( access_t *p_access, uint8_t *p_buffer, size_t sz )
{
  access_sys_t *p_sys = p_access->p_sys;

  //peeracle::Manager::getSingleton().Update();
  p_sys->tracker->Update();
  return -1;
}

static int AccessSeek( access_t *p_access, uint64_t seek_len )
{
  msg_Info(p_access, "AccessSeek!");
  return VLC_EGENERIC;
}