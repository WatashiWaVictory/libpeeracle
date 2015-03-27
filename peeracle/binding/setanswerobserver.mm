#include "setanswerobserver+Internal.h"

@interface SetAnswerObserver

@end

@implementation SetAnswerObserver

- (void) OnSuccess(webrtc::SessionDescriptionInterface *desc)
{
    self.setanswerobserver->OnSuccess(desc);
}

- (void) OnFailure(NSString *msg){
    std::string err_msg([msg cStringUsingEncoding:NSUnicodeStringEncoding]);
    self.setanswerobserver->OnFailure(err_msg);
}


@end