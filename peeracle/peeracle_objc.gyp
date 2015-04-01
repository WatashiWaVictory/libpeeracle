{
  'includes': [
    'build/common.gypi',
  ],
  'variables': {
    'pkg-config': 'pkg-config',
  },

  'conditions': [
    ['OS=="ios" or (OS=="mac" and target_arch!="ia32" and mac_sdk>="10.7")', {
      # The >= 10.7 above is required for ARC.
      'targets': [
        {
          'target_name': 'libpeeracle_objc',
          'type': 'static_library',
          'dependencies': [
            '../talk/libjingle.gyp:libjingle_peerconnection',
          ],
          'sources': [
            'app/webrtc/objc/RTCAudioTrack+Internal.h',
            'app/webrtc/objc/RTCAudioTrack.mm',
            'app/webrtc/objc/RTCDataChannel+Internal.h',
            'app/webrtc/objc/RTCDataChannel.mm',
            'app/webrtc/objc/RTCEnumConverter.h',
            'app/webrtc/objc/RTCEnumConverter.mm',
            'app/webrtc/objc/RTCI420Frame+Internal.h',
            'app/webrtc/objc/RTCI420Frame.mm',
            'app/webrtc/objc/RTCICECandidate+Internal.h',
            'app/webrtc/objc/RTCICECandidate.mm',
            'app/webrtc/objc/RTCICEServer+Internal.h',
            'app/webrtc/objc/RTCICEServer.mm',
            'app/webrtc/objc/RTCMediaConstraints+Internal.h',
            'app/webrtc/objc/RTCMediaConstraints.mm',
            'app/webrtc/objc/RTCMediaConstraintsNative.cc',
            'app/webrtc/objc/RTCMediaConstraintsNative.h',
            'app/webrtc/objc/RTCMediaSource+Internal.h',
            'app/webrtc/objc/RTCMediaSource.mm',
            'app/webrtc/objc/RTCMediaStream+Internal.h',
            'app/webrtc/objc/RTCMediaStream.mm',
            'app/webrtc/objc/RTCMediaStreamTrack+Internal.h',
            'app/webrtc/objc/RTCMediaStreamTrack.mm',
            'app/webrtc/objc/RTCOpenGLVideoRenderer.mm',
            'app/webrtc/objc/RTCPair.m',
            'app/webrtc/objc/RTCPeerConnection+Internal.h',
            'app/webrtc/objc/RTCPeerConnection.mm',
            'app/webrtc/objc/RTCPeerConnectionFactory.mm',
            'app/webrtc/objc/RTCPeerConnectionObserver.h',
            'app/webrtc/objc/RTCPeerConnectionObserver.mm',
            'app/webrtc/objc/RTCSessionDescription+Internal.h',
            'app/webrtc/objc/RTCSessionDescription.mm',
            'app/webrtc/objc/RTCStatsReport+Internal.h',
            'app/webrtc/objc/RTCStatsReport.mm',
            'app/webrtc/objc/RTCVideoCapturer+Internal.h',
            'app/webrtc/objc/RTCVideoCapturer.mm',
            'app/webrtc/objc/RTCVideoRendererAdapter.h',
            'app/webrtc/objc/RTCVideoRendererAdapter.mm',
            'app/webrtc/objc/RTCVideoSource+Internal.h',
            'app/webrtc/objc/RTCVideoSource.mm',
            'app/webrtc/objc/RTCVideoTrack+Internal.h',
            'app/webrtc/objc/RTCVideoTrack.mm',
            'app/webrtc/objc/public/RTCAudioSource.h',
            'app/webrtc/objc/public/RTCAudioTrack.h',
            'app/webrtc/objc/public/RTCDataChannel.h',
            'app/webrtc/objc/public/RTCI420Frame.h',
            'app/webrtc/objc/public/RTCICECandidate.h',
            'app/webrtc/objc/public/RTCICEServer.h',
            'app/webrtc/objc/public/RTCMediaConstraints.h',
            'app/webrtc/objc/public/RTCMediaSource.h',
            'app/webrtc/objc/public/RTCMediaStream.h',
            'app/webrtc/objc/public/RTCMediaStreamTrack.h',
            'app/webrtc/objc/public/RTCOpenGLVideoRenderer.h',
            'app/webrtc/objc/public/RTCPair.h',
            'app/webrtc/objc/public/RTCPeerConnection.h',
            'app/webrtc/objc/public/RTCPeerConnectionDelegate.h',
            'app/webrtc/objc/public/RTCPeerConnectionFactory.h',
            'app/webrtc/objc/public/RTCSessionDescription.h',
            'app/webrtc/objc/public/RTCSessionDescriptionDelegate.h',
            'app/webrtc/objc/public/RTCStatsDelegate.h',
            'app/webrtc/objc/public/RTCStatsReport.h',
            'app/webrtc/objc/public/RTCTypes.h',
            'app/webrtc/objc/public/RTCVideoCapturer.h',
            'app/webrtc/objc/public/RTCVideoRenderer.h',
            'app/webrtc/objc/public/RTCVideoSource.h',
            'app/webrtc/objc/public/RTCVideoTrack.h',
          ],
          'direct_dependent_settings': {
            'include_dirs': [
              '<(DEPTH)/talk/app/webrtc/objc/public',
            ],
          },
          'include_dirs': [
            '<(DEPTH)/talk/app/webrtc',
            '<(DEPTH)/talk/app/webrtc/objc',
            '<(DEPTH)/talk/app/webrtc/objc/public',
          ],
          'link_settings': {
            'libraries': [
              '-lstdc++',
            ],
          },
          'all_dependent_settings': {
            'xcode_settings': {
              'CLANG_ENABLE_OBJC_ARC': 'YES',
            },
          },
          'xcode_settings': {
            'CLANG_ENABLE_OBJC_ARC': 'YES',
            # common.gypi enables this for mac but we want this to be disabled
            # like it is for ios.
            'CLANG_WARN_OBJC_MISSING_PROPERTY_SYNTHESIS': 'NO',
            'DEPLOYMENT_POSTPROCESSING': 'YES',
            'STRIP_INSTALLED_PRODUCT': 'YES',
            'STRIP_STYLE': 'non-global',
          },
          'conditions': [
            ['OS=="ios"', {
              'sources': [
                'app/webrtc/objc/RTCEAGLVideoView.m',
                'app/webrtc/objc/public/RTCEAGLVideoView.h',
              ],
              'link_settings': {
                'xcode_settings': {
                  'OTHER_LDFLAGS': [
                    '-framework CoreGraphics',
                    '-framework GLKit',
                  ],
                },
              },
            }],
            ['OS=="mac"', {
              'sources': [
                'app/webrtc/objc/RTCNSGLVideoView.m',
                'app/webrtc/objc/public/RTCNSGLVideoView.h',
              ],
              'xcode_settings': {
                # Need to build against 10.7 framework for full ARC support
                # on OSX.
                'MACOSX_DEPLOYMENT_TARGET' : '10.7',
              },
              'link_settings': {
                'xcode_settings': {
                  'OTHER_LDFLAGS': [
                    '-framework Cocoa',
                  ],
                },
              },
            }],
          ],
        },  # target libpeeracle_objc
      ],
    }],
    ['OS=="ios" or OS=="mac"', {
      'targets': [
        {
          'target_name': 'peeracle_ios',
          'type': 'executable',
          'product_name': 'AppRTCDemo',
          'mac_bundle': 1,
          'dependencies': [
            'libpeeracle_objc',
          ],
          'conditions': [
            ['OS=="ios"', {
              'mac_bundle_resources': [
                'examples/objc/AppRTCDemo/ios/resources/Default-568h.png',
                'examples/objc/AppRTCDemo/ios/resources/Roboto-Regular.ttf',
                'examples/objc/AppRTCDemo/ios/resources/ic_call_end_black_24dp.png',
                'examples/objc/AppRTCDemo/ios/resources/ic_call_end_black_24dp@2x.png',
                'examples/objc/AppRTCDemo/ios/resources/ic_clear_black_24dp.png',
                'examples/objc/AppRTCDemo/ios/resources/ic_clear_black_24dp@2x.png',
                'examples/objc/Icon.png',
              ],
              'sources': [
                'examples/objc/AppRTCDemo/ios/ARDAppDelegate.h',
                'examples/objc/AppRTCDemo/ios/ARDAppDelegate.m',
                'examples/objc/AppRTCDemo/ios/ARDMainView.h',
                'examples/objc/AppRTCDemo/ios/ARDMainView.m',
                'examples/objc/AppRTCDemo/ios/ARDMainViewController.h',
                'examples/objc/AppRTCDemo/ios/ARDMainViewController.m',
                'examples/objc/AppRTCDemo/ios/ARDVideoCallView.h',
                'examples/objc/AppRTCDemo/ios/ARDVideoCallView.m',
                'examples/objc/AppRTCDemo/ios/ARDVideoCallViewController.h',
                'examples/objc/AppRTCDemo/ios/ARDVideoCallViewController.m',
                'examples/objc/AppRTCDemo/ios/AppRTCDemo-Prefix.pch',
                'examples/objc/AppRTCDemo/ios/UIImage+ARDUtilities.h',
                'examples/objc/AppRTCDemo/ios/UIImage+ARDUtilities.m',
                'examples/objc/AppRTCDemo/ios/main.m',
              ],
              'xcode_settings': {
                'INFOPLIST_FILE': 'examples/objc/AppRTCDemo/ios/Info.plist',
              },
            }],
            ['OS=="mac"', {
              'sources': [
                'examples/objc/AppRTCDemo/mac/APPRTCAppDelegate.h',
                'examples/objc/AppRTCDemo/mac/APPRTCAppDelegate.m',
                'examples/objc/AppRTCDemo/mac/APPRTCViewController.h',
                'examples/objc/AppRTCDemo/mac/APPRTCViewController.m',
                'examples/objc/AppRTCDemo/mac/main.m',
              ],
              'xcode_settings': {
                'CLANG_WARN_OBJC_MISSING_PROPERTY_SYNTHESIS': 'NO',
                'INFOPLIST_FILE': 'examples/objc/AppRTCDemo/mac/Info.plist',
                'MACOSX_DEPLOYMENT_TARGET' : '10.8',
                'OTHER_LDFLAGS': [
                  '-framework AVFoundation',
                ],
              },
            }],
            ['target_arch=="ia32"', {
              'dependencies' : [
                '<(DEPTH)/testing/iossim/iossim.gyp:iossim#host',
              ],
            }],
          ],
        },  
      ],
    }],
  ], # conditions
}
