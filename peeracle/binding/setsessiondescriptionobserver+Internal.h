#include "talk/app/webrtc/jsep.h"
#include "peeracle/peer/setsessiondescriptionobserver.h"
#include "peeracle/peer/peerinterface.h"

@interface SetSessionDescriptionObserver
{
    peeracle::SetSessionDescriptionObserver setsessiondescriptionobserver;
}

@property (nonatomic, assign) peeracle::SetSessionDescriptionObserver setsessiondescriptionobserver;

- (void) OnSuccess(webrtc::SessionDescriptionInterface *desc);

- (void) OnFailure(NSString *msg);

@end