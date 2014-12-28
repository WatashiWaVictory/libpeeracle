C:\MinGW\msys\1.0\bin\rm -rf redist_release
C:\MinGW\msys\1.0\bin\mkdir -p redist_release/lib redist_release/include redist_release/bin
C:\MinGW\msys\1.0\bin\find out/Release -type f ( -name webrtc.lib -or -name webrtc_common.lib -or -name rtc_base.lib -or -name rtc_base_approved.lib -or -name common_audio.lib -or -name common_video.lib -or -name rtc_p2p.lib -or -name rtc_sound.lib -or -name video_engine_core.lib -or -name voice_engine.lib -or -name libjingle_media.lib -or -name libjingle_p2p.lib -or -name libjingle_peerconnection.lib -or -name libwebsockets.lib -or -name peeracle.lib ) -exec C:\MinGW\msys\1.0\bin\mv {} redist_release/lib/ ;
C:\MinGW\msys\1.0\bin\find webrtc talk third_party/libwebsockets -name *.h -exec cp --parents {} redist_release/include/ ;
