#include "talk/app/webrtc/jsep.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "peeracle/peer/createofferobserver.h"
#include "peeracle/peer/peerinterface.h"

@interface CreateOfferObserverObjC
{
    peeracle::CreateOfferObserver createofferobserver;
}

@property (nonatomic, assign) peeracle::CreateOfferObserver createofferobserver;

- (void) OnSuccess(webrtc::SessionDescriptionInterface *desc);

- (void) OnFailure(NSString *msg);

@end
