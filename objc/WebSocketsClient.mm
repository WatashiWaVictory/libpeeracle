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

#import "objc/WebSocketsClient+Internal.h"
#import "third_party/webrtc/webrtc/examples/objc/AppRTCDemo/third_party/SocketRocket/SRWebSocket.h"
#include "objc/WebSocketsClient.h"

namespace peeracle {
  WebSocketsClient::WebSocketsClient(const std::string& url, WebSocketsClientObserver *observer)
  : _url(url), _observer(observer) {
    (void)_observer;
  }
  
  WebSocketsClient::~WebSocketsClient() {
  }
  
  bool WebSocketsClient::Init() {
    // _prclWebSocketsClient = [[PRCLWebSocketsClient alloc] initWithWebSocketsClient:this withURL:[NSURL URLWithString:[NSString stringWithCString:_url.c_str() encoding:[NSString defaultCStringEncoding]]]];
    (void)_url;
    _prclWebSocketsClient = [[PRCLWebSocketsClient alloc] initWithWebSocketsClient:this withObserver:this->_observer withURL:[NSURL URLWithString:@"ws://192.168.1.43:8080"]];
    return true;
  }
  
  bool WebSocketsClient::Connect() {
    [_prclWebSocketsClient connect];
    return true;
  }
  
  bool WebSocketsClient::Update() {
    [_prclWebSocketsClient update];
    return true;
  }
  
  bool WebSocketsClient::Send(const char *buffer, size_t length) {
    [_prclWebSocketsClient send:[NSData dataWithBytes:(const void*)buffer
                                                                      length:length]];
    return true;
  }
  
  bool WebSocketsClient::Disconnect() {
    return false;
  }
}

@implementation PRCLWebSocketsClient {
  peeracle::WebSocketsClientInterface *_nativeWebSocketsClient;
  peeracle::WebSocketsClientObserver *_nativeWebSocketsClientObserver;
  SRWebSocket *_socket;
}
@end

@implementation PRCLWebSocketsClient (Internal)

- (peeracle::WebSocketsClientInterface*)nativeWebSocketsClient {
  return _nativeWebSocketsClient;
}

- (instancetype)initWithWebSocketsClient:(peeracle::WebSocketsClientInterface*)nativeWebSocketsClient withObserver:(peeracle::WebSocketsClientObserver*)observer withURL:(NSURL*)url {
  if (self = [super init]) {
    _nativeWebSocketsClient = nativeWebSocketsClient;
    _nativeWebSocketsClientObserver = observer;
    _socket = [[SRWebSocket alloc] initWithURLRequest:[NSURLRequest requestWithURL:url]];
    _socket.delegate = self;
  }
  return self;
}

- (void)connect {
  [_socket open];
}

- (void)send:(NSData*)data {
  [_socket send:data];
}

- (void)update {
}

- (void)webSocketDidOpen:(SRWebSocket *)webSocket {
  _nativeWebSocketsClientObserver->onConnect();
}

- (void)webSocket:(SRWebSocket *)webSocket didReceiveMessage:(id)message {
  NSString *messageString = message;
  NSData *messageData = [messageString dataUsingEncoding:NSUTF8StringEncoding];
  _nativeWebSocketsClientObserver->onMessage((const char*)[messageData bytes], [messageData length]);
}

- (void)webSocket:(SRWebSocket *)webSocket didFailWithError:(NSError *)error {
  _nativeWebSocketsClientObserver->onError();
}

- (void)webSocket:(SRWebSocket *)webSocket
 didCloseWithCode:(NSInteger)code
           reason:(NSString *)reason
         wasClean:(BOOL)wasClean {
  _nativeWebSocketsClientObserver->onDisconnect();
}

@end
