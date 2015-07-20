/*
 * Copyright (c) 2015 peeracle contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef PEERACLE_SESSION_SESSIONIMPL_H_
#define PEERACLE_SESSION_SESSIONIMPL_H_

#include "third_party/webrtc/webrtc/base/thread.h"
#include "third_party/webrtc/talk/app/webrtc/peerconnectioninterface.h"
#include "peeracle/Session/SessionInterface.h"

namespace peeracle {

class Session::SessionImpl {
 public:
  SessionImpl();
  virtual ~SessionImpl();

  bool Update();

  rtc::Thread *getSignalingThread();
  rtc::Thread *getWorkerThread();
 private:
  rtc::Thread *_signalingThread;
  rtc::Thread *_workerThread;
  rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface>
    _peerConnectionFactory;
};

}  // namespace peeracle

#endif  // PEERACLE_SESSION_SESSIONIMPL_H_