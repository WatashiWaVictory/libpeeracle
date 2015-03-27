#include "setsessiondescriptionobserver+Internal.h"

@interface SetSessionDescriptionObserver

@end

@implementation SetSessionDescriptionObserver

- (void) OnSuccess(webrtc::SessionDescriptionInterface *desc)
{
    self.setsessiondescriptionobserver->OnSuccess(desc);
}

- (void) OnFailure(NSString *msg){
    std::string err_msg([msg cStringUsingEncoding:NSUnicodeStringEncoding]);
    self.setsessiondescriptionobserver->OnFailure(err_msg);
}


@end