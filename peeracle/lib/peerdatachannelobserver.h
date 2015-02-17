#ifndef PEERACLE_PEERDATACHANNELOBSERVER_H_
#define PEERACLE_PEERDATACHANNELOBSERVER_H_

#include "peerdatachannelobserverinterface.h"

namespace peeracle {

class PeerDataChannelObserverInterface;
class PeerDataChannelObserver
    : public PeerDataChannelObserverInterface {
 public:
  PeerDataChannelObserver();

  virtual void OnStateChange();
  virtual void OnMessage(const webrtc::DataBuffer& buffer);

 protected:
  virtual ~PeerDataChannelObserverInterface() {}
};

}

#endif  // PEERACLE_PEERDATACHANNELOBSERVER_H_