#include <talk/app/webrtc/jsep.h>
#include <talk/app/webrtc/peerconnectioninterface.h>
#include "peeracle/peer/createanswerobserver.h"
#include "peeracle/peer/peerinterface.h"

@interface CreateAnswerObserver
{
    peeracle::CreateAnswerObserver createanswerobserver;
}

@property (nonatomic, assign) peeracle::CreateAnswerObserver createanswerobserver;

- (void) OnSuccess(webrtc::SessionDescriptionInterface *desc);

- (void) OnFailure(NSString *error);

@end