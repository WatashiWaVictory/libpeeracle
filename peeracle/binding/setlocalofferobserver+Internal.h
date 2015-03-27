#include "talk/app/webrtc/jsep.h"
#include "peeracle/peer/setlocalobserver.h"
#include "peeracle/peer/peerinterface.h"

@interface SetLocalOfferObserver
{
    peeracle::SetLocalOfferObserver setlocalofferobserver;
}

@property (nonatomic, assign) peeracle::SetLocalOfferObserver setlocalobserver;

- (void) OnSuccess(webrtc::SessionDescriptionInterface *desc);

- (void) OnFailure(NSString *msg);

@end
