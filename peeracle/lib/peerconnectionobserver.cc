#include "third_party/jsoncpp/source/include/json/writer.h"
#include "webrtc/base/logging.h"
#include "peerconnectionobserver.h"

namespace peeracle {

PeerConnectionObserver::PeerConnectionObserver(PeerObserverInterface* observer)
    : observer_(observer) {

}

void PeerConnectionObserver::OnSignalingChange(
  webrtc::PeerConnectionInterface::SignalingState new_state) {
  LOG(LS_INFO) << "OnSignalingChange " << new_state;
}

void PeerConnectionObserver::OnStateChange(StateType state_changed) {
  LOG(LS_INFO) << "OnSignalingChange " << state_changed;
}

void PeerConnectionObserver::OnAddStream(webrtc::MediaStreamInterface *stream) {
  LOG(LS_INFO) << "OnAddStream";
}

void PeerConnectionObserver::OnRemoveStream(webrtc::MediaStreamInterface *stream) {
  LOG(LS_INFO) << "OnRemoveStream";
}

void PeerConnectionObserver::OnDataChannel(webrtc::DataChannelInterface *data_channel) {
  LOG(LS_INFO) << "OnDataChannel " << data_channel->label();
}

void PeerConnectionObserver::OnRenegotiationNeeded() {
  LOG(LS_INFO) << "OnRenegotiationNeeded";
}

void PeerConnectionObserver::OnIceConnectionChange(
  webrtc::PeerConnectionInterface::IceConnectionState new_state) {
  std::string state;

  switch (new_state) {
    case webrtc::PeerConnectionInterface::kIceConnectionNew:
      state = "kIceConnectionNew";
      break;
    case webrtc::PeerConnectionInterface::kIceConnectionChecking:
      state = "kIceConnectionChecking";
      break;
    case webrtc::PeerConnectionInterface::kIceConnectionConnected:
      state = "kIceConnectionConnected";
      break;
    case webrtc::PeerConnectionInterface::kIceConnectionCompleted:
      state = "kIceConnectionCompleted";
      break;
    case webrtc::PeerConnectionInterface::kIceConnectionFailed:
      state = "kIceConnectionFailed";
      break;
    case webrtc::PeerConnectionInterface::kIceConnectionDisconnected:
      state = "kIceConnectionDisconnected";
      break;
    case webrtc::PeerConnectionInterface::kIceConnectionClosed:
      state = "kIceConnectionClosed";
      break;
    default:
      state = "unknown";
      break;
  }

  LOG(LS_INFO) << "OnIceConnectionChange " << state;
}

void PeerConnectionObserver::OnIceGatheringChange(
  webrtc::PeerConnectionInterface::IceGatheringState new_state) {
  LOG(LS_INFO) << "OnIceGatheringChange " << new_state;
}

void PeerConnectionObserver::OnIceCandidate(const webrtc::IceCandidateInterface *candidate) {
  LOG(LS_INFO) << "PeerConnectionObserver::OnIceCandidate";
  Json::FastWriter writer;
  Json::Value jmessage;

  jmessage["sdpMid"] = candidate->sdp_mid();
  jmessage["sdpMLineIndex"] = candidate->sdp_mline_index();
  std::string sdp;
  if (!candidate->ToString(&sdp)) {
    LOG(LS_ERROR) << "Failed to serialize candidate";
    return;
  }
  jmessage["candidate"] = sdp;
  observer_->OnIceCandidate(writer.write(jmessage));
}

void PeerConnectionObserver::OnIceComplete() {
  LOG(LS_INFO) << "OnIceComplete";
}

void PeerConnectionObserver::SetPeerConnection(
  rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection) {
  peer_connection_ = peer_connection;
}

}
