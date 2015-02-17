#include "webrtc/base/ssladapter.h"
#include "webrtc/base/thread.h"
#include "manager.h"

namespace peeracle {

Manager* Manager::singleton_ = NULL;

Manager::Manager() {
  singleton_ = this;

  rtc::AutoThread auto_thread;
  rtc::InitializeSSL();
}

Manager::~Manager() {
  rtc::CleanupSSL();
}

bool Manager::Update() {
  rtc::Thread *thread = rtc::Thread::Current();

  return thread->ProcessMessages(0);
}

}