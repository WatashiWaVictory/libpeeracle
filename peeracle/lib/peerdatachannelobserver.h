#ifndef PEERACLE_PEERDATACHANNELOBSERVER_H_
#define PEERACLE_PEERDATACHANNELOBSERVER_H_

#include "peerdatachannelobserverinterface.h"

namespace peeracle {

class PeerDataChannelObserverInterface;
class PeerDataChannelObserver
    : public PeerDataChannelObserverInterface {
 public:
  PeerDataChannelObserver(webrtc::DataChannelInterface* data_channel);

  virtual void OnStateChange();
  virtual void OnMessage(const webrtc::DataBuffer& buffer);

 private:
  webrtc::DataChannelInterface* data_channel_;

 protected:
  virtual ~PeerDataChannelObserver() {}
};

}

#endif  // PEERACLE_PEERDATACHANNELOBSERVER_H_
