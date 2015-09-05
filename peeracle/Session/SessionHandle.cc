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

#include <iostream>
#include <vector>
#include "peeracle/Session/SessionHandle.h"

namespace peeracle {

SessionHandle::SessionHandle(SessionInterface *session,
                             MetadataInterface *metadata,
                             const std::vector<uint32_t> &got,
                             SessionHandleObserver *observer) :
  _session(session), _observer(observer), _got(got), _metadata(metadata) {
  (void)_session;
  (void)_observer;
}

SessionHandle::~SessionHandle() {
}

MetadataInterface *SessionHandle::getMetadata() const {
  return _metadata;
}

const std::vector<uint32_t> &SessionHandle::getGot() const {
  return _got;
}

void SessionHandle::onPeer(PeerInterface *peer, uint32_t got, bool poke) {
  std::cout << "[SessionHandle] Peer connected " << peer->getId() <<
    " for hash " << _metadata->getId() << " got " << got << " poke " << poke <<
    std::endl;
}

}  // namespace peeracle
