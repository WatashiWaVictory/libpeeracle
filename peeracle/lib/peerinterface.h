#ifndef PEERACLE_PEERINTERFACE_H_
#define PEERACLE_PEERINTERFACE_H_

#include <string>
#include "webrtc/base/refcount.h"

namespace peeracle {

class PeerObserverInterface;
class PeerSetSessionDescriptionObserverInterface;
class PeerInterface {
 public:
  virtual bool Initialize(PeerObserverInterface* observer) = 0;
  virtual void Terminate() = 0;

  virtual void CreateOffer() = 0;
  virtual void CreateAnswer() = 0;

  virtual void SetLocalDescription(
    PeerSetSessionDescriptionObserverInterface* observer,
    const std::string& jobject) = 0;
  virtual void SetRemoteDescription(
    PeerSetSessionDescriptionObserverInterface* observer,
    const std::string& jobject) = 0;

  virtual void AddICECandidate(const std::string& jobject) = 0;

 protected:
  ~PeerInterface() {}
};

}

#endif  // PEERACLE_PEERINTERFACE_H_
