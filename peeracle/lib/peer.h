#ifndef PEERACLE_PEER_H_
#define PEERACLE_PEER_H_

#include "talk/app/webrtc/peerconnectioninterface.h"
#include "mediaconstraints.h"
#include "peercreatesessiondescriptionobserverinterface.h"
#include "peerconnectionobserverinterface.h"
#include "peerobserverinterface.h"
#include "peersetsessiondescriptionobserverinterface.h"
#include "peerinterface.h"

namespace peeracle {

class Peer
    : public PeerInterface {
 public:
  explicit Peer();

  virtual bool Initialize(PeerObserverInterface* observer);
  virtual void Terminate();

  virtual void CreateOffer();
  virtual void CreateAnswer();

  virtual void SetLocalDescription(PeerSetSessionDescriptionObserverInterface*
    observer, const std::string &jobject);
  virtual void SetRemoteDescription(PeerSetSessionDescriptionObserverInterface*
    observer, const std::string &jobject);
  virtual void AddICECandidate(const std::string& jobject);

  PeerObserverInterface* getObserver() const;
  PeerConnectionObserverInterface* getConnectionObserver() const;

 protected:
  virtual ~Peer();

 private:
  rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel_;
  rtc::scoped_refptr<webrtc::DataChannelInterface> signal_channel_;
  rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection_;

  PeerObserverInterface* peer_observer_;
  PeerConnectionObserverInterface* peer_connection_observer_;

  MediaConstraints mediaconstraints_;
};

}  // namespace peeracle

#endif  // PEERACLE_PEER_H_
