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

#if 0
class PeerObserver : public rtc::RefCountInterface {
 public:
  virtual void OnSessionDescription(const std::string& desc) = 0;
  virtual void OnIceCandidate(const std::string& ice) = 0;

 protected:
  ~PeerObserver() {}
};

class Peer {
 public:
  Peer(rtc::scoped_refptr<PeerObserver> observer);

  ~Peer();

  bool Initialize();
  void Terminate();

  void CreateOffer();
  void CreateAnswer();
  void ReceiveSDP(const std::string& jsdp);
  void ReceiveICECandidate(const std::string& jice);

  webrtc::PeerConnectionInterface* getPeerConnection() const;
  PeerObserver* getObserver() const;

  void SetDataChannel(webrtc::DataChannelInterface *channel);
  void SetSignalChannel(webrtc::DataChannelInterface *channel);

 protected:
  class PeerConnectionObserver
    : public webrtc::PeerConnectionObserver {
   public:
    PeerConnectionObserver(Peer& peer);

    void OnSignalingChange(int new_state);
    void OnStateChange(int state_changed);
    void OnAddStream(webrtc::MediaStreamInterface* stream);
    void OnRemoveStream(webrtc::MediaStreamInterface* stream);
    void OnDataChannel(webrtc::DataChannelInterface* data_channel);
    void OnRenegotiationNeeded();
    void OnIceConnectionChange(int new_state);
    void OnIceGatheringChange(int new_state);
    void OnIceCandidate(const webrtc::IceCandidateInterface* candidate);
    void OnIceComplete();

   protected:
    Peer& peer_;
  };

  class DataChannelObserver
    : public webrtc::DataChannelObserver {
   public:
    DataChannelObserver(const Peer& peer);

    void OnStateChange();
    void OnMessage(const webrtc::DataBuffer& buffer);

   private:
    const Peer& peer_;
  };

  class SignalChannelObserver
    : public webrtc::DataChannelObserver {
   public:
    SignalChannelObserver(const Peer& peer);

    void OnStateChange();
    void OnMessage(const webrtc::DataBuffer& buffer);

   private:
    const Peer& peer_;
  };

  class CreateSessionDescriptionObserver
    : public webrtc::CreateSessionDescriptionObserver {
   public:
    void OnSuccess(webrtc::SessionDescriptionInterface* desc);
    void OnFailure(const std::string& error);

   private:
    const Peer& peer_;

   protected:
    CreateSessionDescriptionObserver(const Peer& peer);
  };

  class SetSessionDescriptionObserver
    : public webrtc::SetSessionDescriptionObserver {
   public:
    SetSessionDescriptionObserver();

    void OnSuccess();
    void OnFailure(const std::string& error);
  };

  rtc::scoped_refptr<PeerObserver> peer_observer_;
  PeerConnectionObserver *peer_connection_observer_;
  DataChannelObserver *data_channel_observer_;
  SignalChannelObserver *signal_channel_observer_;

  rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel_;
  rtc::scoped_refptr<webrtc::DataChannelInterface> signal_channel_;
  rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection_;
};

#endif

}  // namespace peeracle

#endif  // PEERACLE_PEER_H_