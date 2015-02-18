#ifndef PEERACLE_PEERCREATESESSIONDESCRIPTIONOBSERVERINTERFACE_H_
#define PEERACLE_PEERCREATESESSIONDESCRIPTIONOBSERVERINTERFACE_H_

namespace peeracle {

class PeerCreateSessionDescriptionObserverInterface
    : public webrtc::CreateSessionDescriptionObserver {
 public:
  virtual void OnSuccess(webrtc::SessionDescriptionInterface* desc) = 0;
  virtual void OnFailure(const std::string& error) = 0;

 protected:
  ~PeerCreateSessionDescriptionObserverInterface() {}
};

}

#endif  // PEERACLE_PEERCREATESESSIONDESCRIPTIONOBSERVERINTERFACE_H_
