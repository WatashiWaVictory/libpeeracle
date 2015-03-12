package org.peeracle;

public interface PeerSetSessionDescriptionObserver {
  public void OnSuccess();
  public void OnFailure(String error);
}
