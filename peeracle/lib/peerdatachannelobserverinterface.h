#ifndef PEERACLE_PEERDATACHANNELOBSERVERINTERFACE_H_
#define PEERACLE_PEERDATACHANNELOBSERVERINTERFACE_H_

#include "talk/app/webrtc/datachannelinterface.h"

namespace peeracle {

class PeerDataChannelObserverInterface
    : public webrtc::DataChannelObserver {
 public:
  virtual void OnStateChange() = 0;
  virtual void OnMessage(const webrtc::DataBuffer& buffer) = 0;

 protected:
  virtual ~PeerDataChannelObserverInterface() {}
};

}

#endif  // PEERACLE_PEERDATACHANNELOBSERVERINTERFACE_H_