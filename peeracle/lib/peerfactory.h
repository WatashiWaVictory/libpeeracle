#ifndef PEERACLE_PEERFACTORY_H_
#define PEERACLE_PEERFACTORY_H_

#include "peerobserverinterface.h"

namespace peeracle {

class PeerInterface;
class PeerFactory {
 public:
  static PeerInterface* Create();
};

}

#endif  // PEERACLE_PEERFACTORY_H_