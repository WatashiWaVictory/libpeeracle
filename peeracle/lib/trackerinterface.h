#ifndef PEERACLE_TRACKERINTERFACE_H_
#define PEERACLE_TRACKERINTERFACE_H_

#include <string>

namespace peeracle {

class TrackerAnnounceObserverInterface;
class TrackerObserverInterface;
class TrackerInterface {
 public:
  virtual bool Initialize(TrackerObserverInterface *observer) = 0;
  virtual bool Update() = 0;
  virtual void Terminate() = 0;

  virtual bool Announce(const std::string& hash, const std::string& got,
    TrackerAnnounceObserverInterface *announceObserver) = 0;

  virtual bool SendSessionDescription(const std::string& peer,
    const std::string& hash, const std::string& sdp) = 0;
  virtual bool SendIceCandidate(const std::string& peer,
    const std::string& hash, const std::string& ice) = 0;

 protected:
  ~TrackerInterface() {}
};

}

#endif  // PEERACLE_TRACKERINTERFACE_H_