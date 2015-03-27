#include <talk/app/webrtc/jsep.h>
#include "peeracle/peer/setanswerobserver.h"
#include "peeracle/peer/peerinterface.h"

@interface SetAnswerObserver
{
    peeracle::SetAnswerObserver setanswerobserver;
}

@property (nonatomic, assign) peeracle::SetAnswerObserver setanswerobserver;

- (void) OnSuccess(webrtc::SessionDescriptionInterface *desc);

- (void) OnFailure(NSString *msg);

@end
