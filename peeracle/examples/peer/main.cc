#include <iostream>
#include <cstring>
#include <map>
#include <cstdlib>
#include <webrtc/base/ssladapter.h>

#include "peeracle/peer/peer.h"

#if 0
#include "peeracle/lib/manager.h"

#include "peeracle/lib/peerfactory.h"
#include "peeracle/lib/peerinterface.h"
#include "peeracle/lib/peerobserverinterface.h"
#include "peeracle/lib/peersetsessiondescriptionobserverinterface.h"

#include "peeracle/lib/trackerinterface.h"
#include "peeracle/lib/trackerfactory.h"
#include "peeracle/lib/trackerobserverinterface.h"
#include "peeracle/lib/trackerannounceobserverinterface.h"
#endif

#define PEERACLE_SAMPLE_HASH "4d5236eba999a8ad85e19c5fac1ce6a929f093d99e4071ded8024fee14e80c66cd156966fc12280746bf9cfe75ec1267c906db23c7d20e6e0ebe0e20b6c62f03"
#define PEERACLE_SAMPLE_GOT "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"

peeracle::Peer *peerA;
peeracle::Peer *peerB;

class MyPeerAObserver : public peeracle::PeerInterface::PeerObserver {
 public:
  explicit MyPeerAObserver() {

  }

  void onIceCandidate(const std::string &sdpMid,
                      int sdpMLineIndex,
                      const std::string &candidate) {
    std::cout << "PeerA ICE : " << peerA << " " << candidate << std::endl;
    peerB->addIceCandidate(sdpMid, sdpMLineIndex, candidate);
  }

  void onSignalingChange(int state) {
    std::cout << "PeerA onSignalingChange : " << state << std::endl;
  }

  void onStateChange(int state) {
    std::cout << "PeerA onStateChange : " << state << std::endl;
  }

  void onIceConnectionChange(int state) {
    std::cout << "PeerA onIceConnectionChange : " << state << std::endl;
  }

  void onIceGatheringChange(int state) {
    std::cout << "PeerA onIceGatheringChange : " << state << std::endl;
  }

  void onIceComplete() {
    std::cout << "PeerA onIceComplete" << std::endl;
  }
};

class MyPeerBObserver : public peeracle::PeerInterface::PeerObserver {
 public:
  explicit MyPeerBObserver() {

  }

  void onIceCandidate(const std::string &sdpMid,
                      int sdpMLineIndex,
                      const std::string &candidate) {
    std::cout << "PeerB ICE : " << peerB << " " << candidate << std::endl;
    peerA->addIceCandidate(sdpMid, sdpMLineIndex, candidate);
  }

  void onSignalingChange(int state) {
    std::cout << "PeerB onSignalingChange : " << state << std::endl;
  }

  void onStateChange(int state) {
    std::cout << "PeerB onStateChange : " << state << std::endl;
  }

  void onIceConnectionChange(int state) {
    std::cout << "PeerB onIceConnectionChange : " << state << std::endl;
  }

  void onIceGatheringChange(int state) {
    std::cout << "PeerB onIceGatheringChange : " << state << std::endl;
  }

  void onIceComplete() {
    std::cout << "PeerB onIceComplete" << std::endl;
  }
};

class MyPeerASessionDescriptionObserver
  : public peeracle::PeerInterface::SessionDescriptionObserver {
 public:
  explicit MyPeerASessionDescriptionObserver(peeracle::PeerInterface *peerA,
                                             peeracle::PeerInterface *peerB);

  void onCreateSuccess(const std::string &sdp, const std::string &type);
  void onSetSuccess();
  void onCreateFailure(const std::string &error);
  void onSetFailure(const std::string &error);

 private:
  peeracle::PeerInterface *_peerA;
  peeracle::PeerInterface *_peerB;
};

class MyPeerBSessionDescriptionObserver :
  public peeracle::PeerInterface::SessionDescriptionObserver {
 public:
  explicit MyPeerBSessionDescriptionObserver(peeracle::PeerInterface *peerA,
                                             peeracle::PeerInterface *peerB) :
    _peerA(peerA), _peerB(peerB) {

  }

  void onCreateSuccess(const std::string &sdp, const std::string &type) {
    std::cout << "PeerB " << std::hex << _peerB << " created answer" <<
      std::endl;

    MyPeerASessionDescriptionObserver *peerAAnswerObserver = new
      MyPeerASessionDescriptionObserver(_peerA, _peerB);

    std::cout << "PeerA " << std::hex << _peerA << " setting answer" <<
      std::endl;
    _peerA->setAnswer(sdp, peerAAnswerObserver);
  }

  void onSetSuccess() {

  }

  void onCreateFailure(const std::string &error) {

  }

  void onSetFailure(const std::string &error) {

  }

 private:
  peeracle::PeerInterface *_peerA;
  peeracle::PeerInterface *_peerB;
};

MyPeerASessionDescriptionObserver::MyPeerASessionDescriptionObserver(
  peeracle::PeerInterface *peerA, peeracle::PeerInterface *peerB) :
    _peerA(peerA), _peerB(peerB) {

}

void MyPeerASessionDescriptionObserver::onCreateSuccess(const std::string
  &sdp, const std::string &type) {
  MyPeerBSessionDescriptionObserver *obs = new
    MyPeerBSessionDescriptionObserver(_peerA, _peerB);

  std::cout << "PeerA " << std::hex << _peerA << " created offer, sending to "
    "PeerB " << std::hex << _peerB << std::endl;

  _peerB->createAnswer(sdp, obs);
}

void MyPeerASessionDescriptionObserver::onSetSuccess() {
  std::cout << "PeerA " << std::hex << _peerA << " set answer" << std::endl;
}

void MyPeerASessionDescriptionObserver::onCreateFailure(const std::string
  &error) {

}

void MyPeerASessionDescriptionObserver::onSetFailure(const std::string
  &error) {

}

int main(int argc, char **argv) {
  rtc::InitializeSSL();

  peerA = new peeracle::Peer();
  peerB = new peeracle::Peer();

  MyPeerAObserver *peerAObserver = new MyPeerAObserver();
  MyPeerBObserver *peerBObserver = new MyPeerBObserver();
  MyPeerASessionDescriptionObserver *peerAOfferObserver = new
    MyPeerASessionDescriptionObserver(peerA, peerB);

  peerA->subscribe(peerAObserver);
  peerB->subscribe(peerBObserver);
  peerA->createOffer(peerAOfferObserver);

  while (true) {
  }

  delete peerAObserver;
  delete peerAOfferObserver;
  delete peerBObserver;
  return EXIT_SUCCESS;
}

#if 0

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

int main(int argc, char **argv) {
  new peeracle::Manager;

  peeracle::TrackerInterface *t = peeracle::TrackerFactory::Create();

  MyTrackerObserver *trackerObserver = new MyTrackerObserver(t);
  t->Initialize(trackerObserver);

  while (peeracle::Manager::getSingleton().Update()) {
    t->Update();
  }

  delete peeracle::Manager::getSingletonPtr();
  return 0;
}

#endif