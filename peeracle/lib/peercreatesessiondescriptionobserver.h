#ifndef PEERACLE_PEERCREATESESSIONDESCRIPTIONOBSERVER_H_
#define PEERACLE_PEERCREATESESSIONDESCRIPTIONOBSERVER_H_

#include <string>
#include "talk/app/webrtc/jsep.h"
#include "peercreatesessiondescriptionobserverinterface.h"
#include "peerobserverinterface.h"

namespace peeracle {

class PeerCreateSessionDescriptionObserver
  : public PeerCreateSessionDescriptionObserverInterface {
 public:
  PeerCreateSessionDescriptionObserver(PeerObserverInterface* observer);

  virtual void OnSuccess(webrtc::SessionDescriptionInterface* desc);
  virtual void OnFailure(const std::string& error);

 private:
  PeerObserverInterface* observer_;

 protected:
  ~PeerCreateSessionDescriptionObserver() {}
};

}

#endif  // PEERACLE_PEERCREATESESSIONDESCRIPTIONOBSERVER_H_