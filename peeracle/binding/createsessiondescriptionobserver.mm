#include <iostream>
#include <webrtc/base/thread.h>
#include "createsessiondescriptionobserver+Internal.h"

@interface CreateSessionDescriptionObserver

@end

@implementation CreateSessionDescriptionObserver

- (void) OnSuccess(webrtc::SessionDescriptionInterface *desc)
{
    self.createsessiondescriptionobserver->OnSuccess(desc);
}

- (void) OnFailure(NSString *msg){
    std::string err_msg([msg cStringUsingEncoding:NSUnicodeStringEncoding]);
    self.createsessiondescriptionobserver->OnFailure(err_msg);
}

@end