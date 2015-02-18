#ifndef PEERACLE_TRACKER_H_
#define PEERACLE_TRACKER_H_

#include <map>
#include <string>
#include <stack>
#include "trackerinterface.h"

namespace Json {
class Value;
}

namespace peeracle {

class TrackerAnnounceObserverInterface;
class TrackerObserverInterface;
class Tracker : public TrackerInterface {
 public:
  explicit Tracker();

  virtual bool Initialize(TrackerObserverInterface *observer);
  virtual bool Update();
  virtual void Terminate();

  virtual bool Announce(const std::string& hash, const std::string& got,
    TrackerAnnounceObserverInterface *announceObserver);

  virtual bool SendSessionDescription(const std::string& peer,
    const std::string& hash, const std::string& sdp);
  virtual bool SendIceCandidate(const std::string& peer,
    const std::string& hash, const std::string& ice);

 public:
  void OnReceive(void *data, size_t length);
  void SendHello();
  void ProcessQueue();
  TrackerObserverInterface* getObserver();

 protected:
  virtual ~Tracker();

 private:
  TrackerObserverInterface* tracker_observer_;
  struct libwebsocket_context *context_;
  struct libwebsocket *wsi_;
  int state_;
  unsigned int callrate_;
  unsigned int lastcall_;

  void Send_(const std::string& buffer);

  std::stack<std::string> queue_;

  typedef void (Tracker::*MessageHandler)(const Json::Value&);
  std::map<std::string, MessageHandler> messagehandlers_;

  void HandleWelcome_(const Json::Value& jmessage);
  void HandleAnnounce_(const Json::Value& jmessage);
  void HandleSignal_(const Json::Value& jmessage);
  void HandleQuit_(const Json::Value& jmessage);

  std::map<std::string, TrackerAnnounceObserverInterface*> announces_;
};

}

#endif  // PEERACLE_TRACKER_H_
