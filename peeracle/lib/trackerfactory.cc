#include "trackerfactory.h"
#include "tracker.h"

namespace peeracle {

TrackerInterface* TrackerFactory::Create() {
  return new Tracker();
}

}