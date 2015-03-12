/**
 * @file       Peer.java
 *
 * @brief      A brief file description.
 * @details    More verbose file description.
 */

package org.peeracle;

/**
 * @class Example
 *
 * @brief A short description of the class
 *
 * A more detailed class description
 */
public class Peer {
  static {
    System.loadLibrary("peeracle_so");
  }

  public static interface Observer {
    public void onIceCandidate(String sdpMid, String sdpMLineIndex, String candidate);
  }

  public static interface SessionDescriptionObserver {
    public void onCreateSuccess(String sdp, String type);
    public void onSetSuccess(String sdp, String type);
    public void onCreateFailure(String error);
    public void onSetFailure(String error);
  }

  public native void createOffer(SessionDescriptionObserver observer);
  public native void createAnswer(SessionDescriptionObserver observer);

  public native void setLocalDescription(SessionDescriptionObserver observer, String type, String sdp);
  public native void setRemoteDescription(SessionDescriptionObserver observer, String type, String sdp);

  public native void addICECandidate(String sdpMid, String sdpMLineIndex, String candidate);

  private final long nativePeer;
  private final long nativeObserver;

  Peer(long nativePeer, long nativeObserver) {
    this.nativePeer = nativePeer;
    this.nativeObserver = nativeObserver;
  }

  public void dispose() {
  }
}
