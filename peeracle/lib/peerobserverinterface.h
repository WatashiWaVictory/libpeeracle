#ifndef PEERACLE_PEEROBSERVERINTERFACE_H_
#define PEERACLE_PEEROBSERVERINTERFACE_H_

#include <string>

namespace peeracle {

class PeerObserverInterface {
 public:
  virtual void OnIceCandidate(const std::string& jobject) = 0;
  virtual void OnSessionDescription(const std::string& jobject) = 0;
 protected:
  ~PeerObserverInterface() {};
};

}

#endif  // PEERACLE_PEEROBSERVERINTERFACE_H_