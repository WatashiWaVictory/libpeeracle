#include "setremoteofferobserver+Internal.h"
#include "createanswerobserver+Internal.h"

@interface  SetRemoteOfferObserver

@end

@implementation SetRemoteOfferObserver

- (void) OnSuccess(webrtc::SessionDescriptionInterface *desc)
{
    self.setremoteofferobserver->OnSuccess(desc);
}

- (void) OnFailure(NSString *msg){
    std::string err_msg([msg cStringUsingEncoding:NSUnicodeStringEncoding]);
    self.setremoteofferobserver->OnFailure(err_msg);
}


@end