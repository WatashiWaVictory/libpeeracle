#include "webrtc/base/logging.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "peer.h"
#include "peerdatachannelobserver.h"

namespace peeracle {

PeerDataChannelObserver::PeerDataChannelObserver(webrtc::DataChannelInterface*
  data_channel)
    : data_channel_(data_channel) {
}

void PeerDataChannelObserver::OnStateChange() {
  LOG(LS_INFO) << "PeerDataChannelObserver::OnStateChange " <<
    data_channel_->label() << " " <<
    webrtc::DataChannelInterface::DataStateString(data_channel_->state());
}

void PeerDataChannelObserver::OnMessage(const webrtc::DataBuffer &buffer) {
  LOG(LS_INFO) << "PeerDataChannelObserver::OnMessage" <<
    data_channel_->label();
}

}
