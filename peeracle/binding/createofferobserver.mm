#include "createofferobserver+Internal.h"
#include "setlocalofferobserver+Internal.h"

@interface CreateOfferObserverObjC

@end

@implementation CreateOfferObserverObjC

- (void) OnSuccess(webrtc::SessionDescriptionInterface *desc){
    self.createofferobserver->OnSuccess(desc);
}

- (void) OnFailure(NSString *msg){
    std::string err_msg([msg cStringUsingEncoding:NSUnicodeStringEncoding]);
    self.createofferobserver->OnFailure(err_msg);
}

@end