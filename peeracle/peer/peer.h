#ifndef PEERACLE_PEER_PEER_H
#define PEERACLE_PEER_PEER_H

#include <list>
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "webrtc/base/scoped_ref_ptr.h"
#include "peerinterface.h"

namespace peeracle {

class Peer
  : public PeerInterface,
    public webrtc::PeerConnectionObserver {
 public:
  explicit Peer();

  void subscribe(PeerInterface::PeerObserver* observer);
  void unsubscribe(PeerInterface::PeerObserver* observer);

  void createOffer(PeerInterface::SessionDescriptionObserver* observer);
  bool createAnswer(const std::string &sdp,
                    PeerInterface::SessionDescriptionObserver* observer);

  bool setAnswer(const std::string &sdp,
                 PeerInterface::SessionDescriptionObserver* observer);

  bool addIceCandidate(const std::string &sdpMid,
                       int sdpMLineIndex,
                       const std::string &candidate);

 private:
  void OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState state);
  void OnStateChange(StateType state_changed);
  void OnAddStream(webrtc::MediaStreamInterface* stream);
  void OnRemoveStream(webrtc::MediaStreamInterface* stream);
  void OnDataChannel(webrtc::DataChannelInterface* data_channel);
  void OnRenegotiationNeeded();
  void OnIceConnectionChange(
    webrtc::PeerConnectionInterface::IceConnectionState new_state);
  void OnIceGatheringChange(
    webrtc::PeerConnectionInterface::IceGatheringState new_state);
  void OnIceCandidate(const webrtc::IceCandidateInterface* candidate);
  void OnIceComplete();

  std::list<PeerInterface::PeerObserver*> _peerObservers;

  rtc::scoped_refptr<webrtc::PeerConnectionInterface> _peerConnection;

  rtc::Thread *_signaling_thread;
  rtc::Thread *_worker_thread;
  rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface>
    _peerConnectionFactory;
};

}

#endif