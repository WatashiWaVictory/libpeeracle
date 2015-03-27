#include <talk/app/webrtc/jsep.h>
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "peeracle/peer/setremoteofferobserver.h"
#include "peeracle/peer/peerinterface.h"

@interface SetRemoteOfferObserver
{
    peeracle::SetRemoteOfferObserver setremoteofferobserver,
}

@property (nonatomic, assign) peeracle::SetRemoteOfferObserver setremoteofferobserver;

- (void) OnSuccess(webrtc::SessionDescriptionInterface *desc);

- (void) OnFailure(NSString *msg);

@end