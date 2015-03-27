#include "setlocalofferobserver+Internal.h"

@interface SetLocalOfferObserver

@end

@implementation SetLocalOfferObserver

- (void) OnSuccess(webrtc::SessionDescriptionInterface *desc)
{
    self.setlocalofferobserver->OnSuccess(desc);
}

- (void) OnFailure(NSString *msg){
    std::string err_msg([msg cStringUsingEncoding:NSUnicodeStringEncoding]);
    self.setlocalofferobserver->OnFailure(err_msg);
}

@end
