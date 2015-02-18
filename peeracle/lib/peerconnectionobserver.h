#ifndef PEERACLE_PEERCONNECTIONOBSERVER_H_
#define PEERACLE_PEERCONNECTIONOBSERVER_H_

#include "talk/app/webrtc/peerconnectioninterface.h"
#include "peerconnectionobserverinterface.h"
#include "peerobserverinterface.h"

namespace peeracle {

class PeerConnectionObserver
    : public PeerConnectionObserverInterface {
 public:
  PeerConnectionObserver(PeerObserverInterface* observer);

  virtual void OnSignalingChange(
    webrtc::PeerConnectionInterface::SignalingState new_state);
  virtual void OnStateChange(StateType state_changed);
  virtual void OnAddStream(webrtc::MediaStreamInterface* stream);
  virtual void OnRemoveStream(webrtc::MediaStreamInterface* stream);
  virtual void OnDataChannel(webrtc::DataChannelInterface* data_channel);
  virtual void OnRenegotiationNeeded();
  virtual void OnIceConnectionChange(
    webrtc::PeerConnectionInterface::IceConnectionState new_state);
  virtual void OnIceGatheringChange(
    webrtc::PeerConnectionInterface::IceGatheringState new_state);
  virtual void OnIceCandidate(const webrtc::IceCandidateInterface* candidate);
  virtual void OnIceComplete();
  virtual void SetPeerConnection(
    rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection);

 private:
  PeerObserverInterface* observer_;
  rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection_;

 protected:
  ~PeerConnectionObserver() {}
};

}

#endif  // PEERACLE_PEERCONNECTIONOBSERVER_H_
