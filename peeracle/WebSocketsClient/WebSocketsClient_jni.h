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

#ifndef PEERACLE_WEBSOCKETSCLIENT_WEBSOCKETSCLIENT_JNI_H_
#define PEERACLE_WEBSOCKETSCLIENT_WEBSOCKETSCLIENT_JNI_H_

#include <string>
#include "peeracle/WebSocketsClient/WebSocketsClientInterface.h"
#include "peeracle/WebSocketsClient/WebSocketsClientObserver.h"
#include "java/jni/classreferenceholder.h"
#include "java/jni/jni_helpers.h"

namespace peeracle {

class JNIWebSocketsClient : public WebSocketsClientInterface {
 public:
  JNIWebSocketsClient(const std::string& url,
                      WebSocketsClientObserver *observer);
  ~JNIWebSocketsClient();

  bool Init();
  bool Connect();
  bool Update();
  bool Send(const char *buffer, size_t length);
  bool Disconnect();

 private:
  const ScopedGlobalRef<jclass> _j_class;
  jmethodID _j_init;
  const ScopedGlobalRef<jobject> _j_global;
};

}  // namespace peeracle

#endif  // PEERACLE_WEBSOCKETSCLIENT_WEBSOCKETSCLIENT_JNI_H_
