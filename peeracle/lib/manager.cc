#include <webrtc/system_wrappers/interface/trace.h>
#include <iostream>
#include <talk/app/webrtc/peerconnectioninterface.h>
#include "webrtc/base/ssladapter.h"
#include "webrtc/base/thread.h"
#include "manager.h"

namespace peeracle {

Manager* Manager::singleton_ = NULL;

Manager::Manager() {
  singleton_ = this;

  rtc::InitializeSSL();
  rtc::ThreadManager::Instance()->WrapCurrentThread();
  webrtc::Trace::CreateTrace();

  worker_thread_ = new rtc::Thread();
  worker_thread_->SetName("worker_thread", NULL);

  signaling_thread_ = new rtc::Thread();
  signaling_thread_->SetName("signaling_thread", NULL);

  if (!worker_thread_->Start() || !signaling_thread_->Start())
    std::cerr << "Failed to start threads" << std::endl;

  rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> factory(
    webrtc::CreatePeerConnectionFactory(worker_thread_,
      signaling_thread_,
      NULL,
      NULL,
      NULL));

  peerconnection_factory_ = factory.release();
}

Manager::~Manager() {
  peerconnection_factory_->Release();
  rtc::CleanupSSL();
}

bool Manager::Update() {
  rtc::Thread *thread = rtc::Thread::Current();

  return thread->ProcessMessages(0);
}

}
