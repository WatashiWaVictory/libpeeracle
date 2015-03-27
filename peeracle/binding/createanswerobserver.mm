#include <webrtc/base/scoped_ref_ptr.h>
#include "createanswerobserver+Internal.h"
#include "setanswerobserver+Internal.h"

@interface CreateAnswerObserverObjC

@end

@implementation CreateAnswerObserverObjC

- (void) OnSuccess(webrtc::SessionDescriptionInterface *desc)
{
    self.createanswerobserver->OnSuccess(desc);
}

- (void) OnFailure(NSString *msg){
    std::string err_msg([msg cStringUsingEncoding:NSUnicodeStringEncoding]);
    self.createanswerobserver->OnFailure(err_msg);
}

@end