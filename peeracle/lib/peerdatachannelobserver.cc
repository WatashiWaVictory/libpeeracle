#include "webrtc/base/logging.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "peer.h"
#include "peerdatachannelobserver.h"

namespace peeracle {

PeerDataChannelObserver::PeerDataChannelObserver() {
}

void PeerDataChannelObserver::OnStateChange() {
  LOG(LS_INFO) << "DataChannelObserver OnStateChange";
}

void PeerDataChannelObserver::OnMessage(const webrtc::DataBuffer &buffer) {
  LOG(LS_INFO) << "DataChannelObserver OnMessage";
}

}