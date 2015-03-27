#include <list>
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "webrtc/base/scoped_ref_ptr.h"
#include "peeracle/peer/peer.h"
#include "peeracle/peer/peerinterface.h"

@interface Peer
{
    peeracle::Peer peer;
}

@property (nonatomic, assign) peeracle::Peer peer;

-(void) subscribe(peeracle::PeerInterface::PeerObserver* observer);

-(void) unsuscribe(peeracle::PeerInterface::PeerObserver* observer);

-(void) createOffer(peeracle::PeerInterface::SessionDescriptionObserver* observer);

-(void) createAnswer(NSString *sdp, peeracle::PeerInterface::SessionDescriptionObserver* observer);

-(void) setAnswer(NSString *sdp, peeracle::PeerInterface::SessionDescriptionObserver* observer);

-(void) addIceCandidate(NSString *sdp, int sdpMLineIndex, NSString *candidate);

@end