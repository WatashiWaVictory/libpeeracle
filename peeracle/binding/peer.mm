#include <iostream>
#include "talk/app/webrtc/test/fakeconstraints.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "webrtc/base/thread.h"
#include "createofferobserver+Internal.h"
#include "setremoteofferobserver+Internal.h"
#include "setsessiondescriptionobserver+Internal.h"
#include "peer+Internal.h"

@interface Peer

@end

@implementation Peer

-(void) subscribe(peeracle::PeerInterface::PeerObserver* observer)
{
    self.peer->subscribe(observer);
}

-(void) unsuscribe(peeracle::PeerInterface::PeerObserver* observer)
{
    self.peer->unsuscribe(observer);
}

-(void) createOffer(peeracle::PeerInterface::SessionDescriptionObserver* observer)
{
    self.peer->createOffer(observer);
}

-(void) createAnswer(NSString *sdp, peeracle::PeerInterface::SessionDescriptionObserver* observer)
{
    std::string nsSdp([msg cStringUsingEncoding:NSUnicodeStringEncoding]);
    self.peer->createAnswer(nsSdp, observer);
}

-(void) setAnswer(NSString *sdp, peeracle::PeerInterface::SessionDescriptionObserver* observer)
{
    std::string nsSdp([sdp cStringUsingEncoding:NSUnicodeStringEncoding]);
    self.peer->setAnswer(nsSdp, observer);
}

-(void) addIceCandidate(NSString *sdp, int sdpMLineIndex, NSString *candidate)
{
    std::string nsSdp([sdp cStringUsingEncoding:NSUnicodeStringEncoding]);
    std::string nsCandidate([candidate cStringUsingEncoding:NSUnicodeStringEncoding]);
    self.peer->addIceCandidate(nsSdp, sdpMLineIndex, candidate);
}

@end