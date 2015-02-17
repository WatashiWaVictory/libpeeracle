#ifndef PEERACLE_TRACKERANNOUNCEOBSERVERINTERFACE_H_
#define PEERACLE_TRACKERANNOUNCEOBSERVERINTERFACE_H_

namespace peeracle {

class TrackerAnnounceObserverInterface {
 public:
  virtual void OnPeerConnect(const std::string& id, const std::string& got) = 0;
  virtual void OnPeerDisconnect(const std::string& id) = 0;

  virtual void OnOffer(const std::string& id,
    const std::string& sdp) = 0;
  virtual void OnAnswer(const std::string& id,
    const std::string& sdp) = 0;
  virtual void OnIceCandidate(const std::string& id,
    const std::string& ice) = 0;

 protected:
  ~TrackerAnnounceObserverInterface() {};
};

}

#endif  // PEERACLE_TRACKERANNOUNCEOBSERVERINTERFACE_H_