#include "peerfactory.h"
#include "peer.h"

namespace peeracle {

PeerInterface* PeerFactory::Create() {
  Peer* peer = new Peer();
  return peer;
}

}
