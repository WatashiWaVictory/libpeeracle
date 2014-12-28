rm -rf redist_release

mkdir -p redist_release/lib redist_release/include redist_release/bin

find out/Release -type f \( -name libwebrtc.a -or -name libwebrtc_common.a -or -name librtc_base.a -or -name librtc_base_approved.a -or -name libcommon_audio.a -or -name libcommon_video.a -or -name librtc_p2p.a -or -name librtc_sound.a -or -name libvideo_engine_core.a -or -name libvoice_engine.a -or -name libjingle_media.a -or -name libjingle_p2p.a -or -name libjingle_peerconnection.a -or -name libwebsockets.a -or -name libpeeracle.a \) -exec mv {} redist_release/lib/ \;
