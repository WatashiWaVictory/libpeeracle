#include "talk/app/webrtc/jsep.h"
#include "peeracle/peer/createsessiondescriptionobserver.h"
#include "peeracle/peer/peerinterface.h"

@interface CreateSessionDescriptionObserver
{
    peeracle::CreateSessionDescriptionObserver createsessiondescriptionobserver;
}

@property (nonatomic, assign) peeracle::CreateSessionDescriptionObserver createsessiondescriptionobserver;

-(void) OnSuccess(webrtc::SessionDescriptionInterface* desc);

-(void) OnFailure(NSString *msg);

@end