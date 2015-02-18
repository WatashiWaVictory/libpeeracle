{
  'includes': [
    'build/common.gypi',
  ],
  'targets': [
    {
      'target_name': 'peeracle',
      'type': 'static_library',
      'dependencies': [
        '../third_party/jsoncpp/jsoncpp.gyp:jsoncpp',
        '../talk/libjingle.gyp:libjingle',
        '../talk/libjingle.gyp:libjingle_p2p',
        '../talk/libjingle.gyp:libjingle_peerconnection',
        '../third_party/libwebsockets/libwebsockets.gyp:*',
      ],
      'sources': [
        'lib/metadata.cc',
        'lib/peer.cc',
        'lib/peerfactory.cc',
        'lib/peerconnectionobserver.cc',
        'lib/peercreatesessiondescriptionobserver.cc',
        'lib/peerdatachannelobserver.cc',
        #'lib/peersetsessiondescriptionobserver.cc',
        'lib/manager.cc',
        'lib/tracker.cc',
        'lib/trackerfactory.cc',
        'lib/gettimeofday.cc',
      ],
      'include_dirs': [
        '../third_party/jsoncpp/source/include/',
      ],
    },
  ],
}
