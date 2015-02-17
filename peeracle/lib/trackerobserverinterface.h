#ifndef PEERACLE_TRACKEROBSERVERINTERFACE_H_
#define PEERACLE_TRACKEROBSERVERINTERFACE_H_

namespace peeracle {

class TrackerObserverInterface {
 public:
  virtual void OnConnect() = 0;
  virtual void OnDisconnect() = 0;

 protected:
  ~TrackerObserverInterface() {};
};

}

#endif  // PEERACLE_TRACKEROBSERVERINTERFACE_H_