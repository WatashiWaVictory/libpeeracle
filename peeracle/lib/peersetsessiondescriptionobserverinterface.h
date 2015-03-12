#ifndef PEERACLE_PEERSETSESSIONDESCRIPTIONOBSERVERINTERFACE_H_
#define PEERACLE_PEERSETSESSIONDESCRIPTIONOBSERVERINTERFACE_H_

#include <talk/app/webrtc/jsep.h>

namespace peeracle {

class PeerSetSessionDescriptionObserverInterface :
  public webrtc::SetSessionDescriptionObserver {
 public:
  virtual void OnSuccess() = 0;
  virtual void OnFailure(const std::string& error) = 0;

 protected:
  virtual ~PeerSetSessionDescriptionObserverInterface() {};
};

}

#endif  // PEERACLE_PEERSETDESCRIPTIONOBSERVERINTERFACE_H_
