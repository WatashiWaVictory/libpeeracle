{
  'includes': [
    'build/common.gypi',
  ],
  'targets': [
    {
      'target_name': 'peeracle',
      'type': 'static_library',
      'dependencies': [
        '../talk/libjingle.gyp:libjingle',
        '../talk/libjingle.gyp:libjingle_p2p',
        '../third_party/libwebsockets/libwebsockets.gyp:*',
      ],
      'sources': [
        'lib/peeracle.cc',
      ],
    },
  ],
}
