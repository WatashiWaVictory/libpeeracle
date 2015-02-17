#include "webrtc/base/logging.h"
#include "third_party/jsoncpp/source/include/json/writer.h"
#include "peercreatesessiondescriptionobserver.h"

namespace peeracle {

PeerCreateSessionDescriptionObserver::PeerCreateSessionDescriptionObserver
  (PeerObserverInterface* observer) : observer_(observer) {
}

void PeerCreateSessionDescriptionObserver::OnSuccess(webrtc::SessionDescriptionInterface *desc) {
  LOG(LS_INFO) << "PeerCreateSessionDescriptionObserver::OnSuccess";
  Json::FastWriter writer;
  Json::Value jmessage;
  jmessage["type"] = desc->type();
  std::string sdp;
  if (!desc->ToString(&sdp)) {
    LOG(LS_ERROR) << "Failed to serialize sdp";
    return;
  }
  jmessage["sdp"] = sdp;
  observer_->OnSessionDescription(writer.write(jmessage));
}

void PeerCreateSessionDescriptionObserver::OnFailure(const std::string &error) {
  LOG(LS_INFO) << "PeerCreateSessionDescriptionObserver::OnFailure";
}

}