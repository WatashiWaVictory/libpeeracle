package org.peeracle;

public interface PeerCreateSessionDescriptionObserver {
  public void onSuccess(String sdp, String type);
  public void onFailure(String error);
}
