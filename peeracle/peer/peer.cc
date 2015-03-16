#include <iostream>
#include "talk/app/webrtc/test/fakeconstraints.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "webrtc/base/thread.h"
#include "createofferobserver.h"
#include "setremoteofferobserver.h"
#include "setsessiondescriptionobserver.h"
#include "peer.h"

namespace peeracle {

Peer::Peer() {
  webrtc::PeerConnectionInterface::IceServers iceServers;
  webrtc::PeerConnectionInterface::IceServer iceServer;
  iceServer.uri = "stun:stun.l.google.com:19302";
  iceServers.push_back(iceServer);

  webrtc::FakeConstraints constr;
  constr.AddOptional(webrtc::MediaConstraintsInterface::kEnableDtlsSrtp,
    webrtc::MediaConstraintsInterface::kValueTrue);
  constr.AddMandatory(webrtc::MediaConstraintsInterface::kOfferToReceiveAudio,
    webrtc::MediaConstraintsInterface::kValueFalse);
  constr.AddMandatory(webrtc::MediaConstraintsInterface::kOfferToReceiveVideo,
    webrtc::MediaConstraintsInterface::kValueFalse);

  rtc::ThreadManager::Instance()->WrapCurrentThread();
  _worker_thread = new rtc::Thread();
  _worker_thread->SetName("worker_thread", NULL);
  _signaling_thread = new rtc::Thread();
  _signaling_thread->SetName("signaling_thread", NULL);
  CHECK(_worker_thread->Start() && _signaling_thread->Start())
    << "Failed to start threads";

  _peerConnectionFactory = webrtc::CreatePeerConnectionFactory(_worker_thread,
    _signaling_thread, NULL, NULL, NULL);

  _peerConnection = _peerConnectionFactory->CreatePeerConnection(iceServers,
    &constr, NULL, NULL, this);
}

void Peer::subscribe(PeerInterface::PeerObserver* observer) {
  _peerObservers.push_back(observer);
}

void Peer::unsubscribe(PeerInterface::PeerObserver* observer) {
  std::remove(_peerObservers.begin(), _peerObservers.end(), observer);
}

void Peer::createOffer(PeerInterface::SessionDescriptionObserver* observer) {
  rtc::scoped_refptr<CreateOfferObserver>
    createOfferObserver =
    new rtc::RefCountedObject<CreateOfferObserver>
      (_peerConnection, observer);

  // webrtc::DataChannelInit dataChannelInit;
  // _dataChannel = _peerConnection->CreateDataChannel("signal",
  //  &dataChannelInit);

  _peerConnection->CreateOffer(createOfferObserver, NULL);
}

bool Peer::createAnswer(const std::string &sdp,
                        PeerInterface::SessionDescriptionObserver* observer) {
  webrtc::SessionDescriptionInterface *desc =
    webrtc::CreateSessionDescription("offer", sdp);

  if (!desc) {
    return false;
  }

  rtc::scoped_refptr<SetRemoteOfferObserver>
    setRemoteOfferObserver =
    new rtc::RefCountedObject<SetRemoteOfferObserver>
      (_peerConnection, observer);

  _peerConnection->SetRemoteDescription(setRemoteOfferObserver, desc);
  return true;
}

bool Peer::setAnswer(const std::string &sdp,
                     PeerInterface::SessionDescriptionObserver* observer) {
  webrtc::SessionDescriptionInterface *desc =
    webrtc::CreateSessionDescription("answer", sdp);

  if (!desc) {
    return false;
  }

  rtc::scoped_refptr<SetSessionDescriptionObserver>
    setAnswerObserver =
    new rtc::RefCountedObject<SetSessionDescriptionObserver>
      (observer);

  _peerConnection->SetRemoteDescription(setAnswerObserver, desc);
  return true;
}

bool Peer::addIceCandidate(const std::string &sdpMid,
                           int sdpMLineIndex,
                           const std::string &candidate) {
  rtc::scoped_ptr<webrtc::IceCandidateInterface> iceCandidate(
    webrtc::CreateIceCandidate(sdpMid, sdpMLineIndex, candidate));

  if (!iceCandidate) {
    return false;
  }

  _peerConnection->AddIceCandidate(iceCandidate.get());
  return true;
}

void Peer::OnSignalingChange
  (webrtc::PeerConnectionInterface::SignalingState state) {
  for (std::list<PeerInterface::PeerObserver*>::iterator it =
    _peerObservers.begin(); it != _peerObservers.end(); ++it) {
    (*it)->onSignalingChange(state);
  }
}

void Peer::OnStateChange(StateType state_changed) {
  for (std::list<PeerInterface::PeerObserver*>::iterator it =
    _peerObservers.begin(); it != _peerObservers.end(); ++it) {
    (*it)->onStateChange(state_changed);
  }
}

void Peer::OnAddStream(webrtc::MediaStreamInterface* stream) {
  std::cout << "Peer::OnAddStream " << std::endl;
}

void Peer::OnRemoveStream(webrtc::MediaStreamInterface* stream) {
  std::cout << "Peer::OnRemoveStream " << std::endl;
}

void Peer::OnDataChannel(webrtc::DataChannelInterface* data_channel) {
  std::cout << "Peer::OnDataChannel " << data_channel->label() <<
    std::endl;
}

void Peer::OnRenegotiationNeeded() {
  std::cout << "Peer::OnRenegotiationNeeded " << std::endl;
}

void Peer::OnIceConnectionChange(
  webrtc::PeerConnectionInterface::IceConnectionState new_state) {
  for (std::list<PeerInterface::PeerObserver*>::iterator it =
    _peerObservers.begin(); it != _peerObservers.end(); ++it) {
    (*it)->onIceConnectionChange(new_state);
  }
}

void Peer::OnIceGatheringChange(
  webrtc::PeerConnectionInterface::IceGatheringState new_state) {
  for (std::list<PeerInterface::PeerObserver*>::iterator it =
    _peerObservers.begin(); it != _peerObservers.end(); ++it) {
    (*it)->onIceGatheringChange(new_state);
  }
}

void Peer::OnIceCandidate(const webrtc::IceCandidateInterface* candidate) {
  std::string cand;

  candidate->ToString(&cand);
  for (std::list<PeerInterface::PeerObserver*>::iterator it =
    _peerObservers.begin(); it != _peerObservers.end(); ++it) {
    (*it)->onIceCandidate(candidate->sdp_mid(), candidate->sdp_mline_index(),
      cand);
  }
}

void Peer::OnIceComplete() {
  std::cout << "Peer::OnIceComplete " <<
    std::endl;
}

}