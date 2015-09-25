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

#import "public/SessionObserver.h"
#import "Session+Internal.h"
#import "Metadata+Internal.h"
#include "MemoryStorage.h"
//#import "public/SessionHandleObserver.h"

#include "peeracle/Session/Session.h"

namespace peeracle {
  class PRCLSessionObserver : public SessionObserver {
  public:
    PRCLSessionObserver(id<PRCLSessionDelegate> delegate) {
      _delegate = delegate;
    }
    
    void setSession(PRCLSession *session) {
      _session = session;
    }
    
  private:
    __weak PRCLSession* _session;
    id<PRCLSessionDelegate> _delegate;
  };
  
  class PRCLSessionHandleObserver : public SessionHandleObserver {
  public:
    PRCLSessionHandleObserver(id<PRCLSessionHandleDelegate> delegate) {
      _delegate = delegate;
    }
    
    void setSessionHandle(PRCLSessionHandle *sessionHandle) {
      _sessionHandle = sessionHandle;
    }
    
    void onEnter(PeerInterface *peer)
    {
      
    }
    
    void onLeave(PeerInterface *peer)
    {
      
    }
    
    void onRequest(PeerInterface *peer, uint32_t segment, uint32_t chunk)
    {
      
    }
    
    void onChunk(PeerInterface *peer, uint32_t segment, uint32_t chunk, uint32_t offset, const char *bytes, uint32_t length)
    {
      
    }
    
    void onMediaSegment(uint32_t segment, const char *bytes, uint32_t length)
    {
      
    }
    
  private:
    __weak PRCLSessionHandle* _sessionHandle;
    id<PRCLSessionHandleDelegate> _delegate;
  };}

@implementation PRCLSession

@synthesize nativeSession = _nativeSession;
@synthesize nativeStorage = _nativeStorage;

- (bool) update {
  return _nativeSession->update();
}

- (NSMutableDictionary *) vgetHandles {
  return _handles;
}

- (NSMutableDictionary *) vgetPeers {
  return _peers;
}

- (PRCLSessionHandle*)addMetadata:(Metadata*)metadata withDelegate:(id<PRCLSessionHandleDelegate>)delegate {
  PRCLSessionHandle *handle = [PRCLSessionHandle alloc];
  
  peeracle::PRCLSessionHandleObserver *observer = new peeracle::PRCLSessionHandleObserver(delegate);
  peeracle::SessionHandleInterface *nativeSessionHandle =
    _nativeSession->addMetadata(metadata.nativeMetadata, observer);
  handle.nativeSessionHandle = nativeSessionHandle;
  return handle;
}

- (id) initWithDelegate:(id<PRCLSessionDelegate>)delegate {
  peeracle::PRCLSessionObserver *observer = new peeracle::PRCLSessionObserver(delegate);
  peeracle::MemoryStorage *memory = new peeracle::MemoryStorage();
  self.nativeSession = new peeracle::Session(memory, observer);
  observer->setSession(self);
  return self;
}

@end
