#ifndef PEERACLE_PEERSETSESSIONDESCRIPTIONOBSERVERINTERFACE_H_
#define PEERACLE_PEERSETSESSIONDESCRIPTIONOBSERVERINTERFACE_H_

namespace peeracle {

class PeerSetSessionDescriptionObserverInterface {
 public:
  virtual void OnSuccess() = 0;
  virtual void OnFailure(const std::string& error) = 0;

 protected:
  ~PeerSetSessionDescriptionObserverInterface() {};
};

}

#endif  // PEERACLE_PEERSETDESCRIPTIONOBSERVERINTERFACE_H_
