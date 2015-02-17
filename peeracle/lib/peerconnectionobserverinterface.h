#ifndef PEERACLE_PEERCONNECTIONOBSERVERINTERFACE_H_
#define PEERACLE_PEERCONNECTIONOBSERVERINTERFACE_H_

namespace peeracle {

class PeerConnectionObserverInterface
    : public webrtc::PeerConnectionObserver {
 public:
  virtual void OnSignalingChange(
    webrtc::PeerConnectionInterface::SignalingState new_state) = 0;
  virtual void OnStateChange(StateType state_changed) = 0;
  virtual void OnAddStream(webrtc::MediaStreamInterface* stream) = 0;
  virtual void OnRemoveStream(webrtc::MediaStreamInterface* stream) = 0;
  virtual void OnDataChannel(webrtc::DataChannelInterface* data_channel) = 0;
  virtual void OnRenegotiationNeeded() = 0;
  virtual void OnIceConnectionChange(
    webrtc::PeerConnectionInterface::IceConnectionState new_state) = 0;
  virtual void OnIceGatheringChange(
    webrtc::PeerConnectionInterface::IceGatheringState new_state) = 0;
  virtual void OnIceCandidate(const webrtc::IceCandidateInterface* candidate) = 0;
  virtual void OnIceComplete() = 0;

 protected:
  ~PeerConnectionObserverInterface() {}
};

}

#endif  // PEERACLE_PEERCONNECTIONOBSERVER_H_