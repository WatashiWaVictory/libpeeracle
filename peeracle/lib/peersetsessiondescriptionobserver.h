#ifndef PEERACLE_PEERSETSESSIONDESCRIPTIONOBSERVER_H_
#define PEERACLE_PEERSETSESSIONDESCRIPTIONOBSERVER_H_

namespace peeracle {

class PeerSetSessionDescriptionObserver
    : public PeerSetSessionDescriptionObserverInterface {
 public:
  virtual void OnSuccess();
  virtual void OnFailure(const std::string& error);

 protected:
  ~PeerSetSessionDescriptionObserver() {};
};

}

#endif  // PEERACLE_PEERSETSESSIONDESCRIPTIONOBSERVER_H_
