#ifndef PEERACLE_TRACKERFACTORY_H_
#define PEERACLE_TRACKERFACTORY_H_

#include "trackerinterface.h"

namespace peeracle {

class TrackerFactory {
 public:
  static TrackerInterface* Create();
};

}

#endif  // PEERACLE_TRACKERFACTORY_H_