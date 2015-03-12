{
  'includes': [
    'build/common.gypi',
  ],
  'targets': [
    {
      'target_name': 'peer',
      'type': 'executable',
      'dependencies': [
        'peeracle.gyp:peeracle_peer',
      ],
      'sources': [
        'examples/peer/main.cc',
      ],
    },
    {
      'target_name': 'tracker',
      'type': 'executable',
      'dependencies': [
        '../third_party/libwebsockets/libwebsockets.gyp:*',
      ],
      'sources': [
        'examples/tracker/main.cc',
      ],
    },
  ],
}
