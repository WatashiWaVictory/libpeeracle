{
  'includes': [
    'build/common.gypi',
  ],
  'variables': {
    'pkg-config': 'pkg-config',
  },
  'targets': [
#   {
#     'target_name': 'peeracle',
#     'type': 'static_library',
#     'dependencies': [
#       '../third_party/jsoncpp/jsoncpp.gyp:jsoncpp',
#       '../talk/libjingle.gyp:libjingle',
#       '../talk/libjingle.gyp:libjingle_p2p',
#       '../talk/libjingle.gyp:libjingle_peerconnection',
#       '../third_party/libwebsockets/libwebsockets.gyp:*',
#     ],
#     'sources': [
#       'lib/metadata.cc',
#       'lib/peer.cc',
#       'lib/peerfactory.cc',
#       'lib/peerconnectionobserver.cc',
#       'lib/peercreatesessiondescriptionobserver.cc',
#       'lib/peerdatachannelobserver.cc',
#       #'lib/peersetsessiondescriptionobserver.cc',
#       'lib/manager.cc',
#       'lib/tracker.cc',
#       'lib/trackerfactory.cc',
#       'lib/gettimeofday.cc',
#     ],
#     'include_dirs': [
#       '../third_party/jsoncpp/source/include/',
#     ],
#   }, # target peeracle
    {
      'target_name': 'peeracle_peer',
      'type': 'static_library',
      'dependencies': [
        '../talk/libjingle.gyp:libjingle_peerconnection',
      ],
      'sources': [
        'peer/createanswerobserver.cc',
        'peer/createofferobserver.cc',
        'peer/createsessiondescriptionobserver.cc',
        'peer/peer.cc',
        'peer/setanswerobserver.cc',
        'peer/setlocalofferobserver.cc',
        'peer/setremoteofferobserver.cc',
        'peer/setsessiondescriptionobserver.cc',
      ],
    }, # target peeracle_peer
    {
      'target_name': 'peeracle_tracker',
      'type': 'static_library',
      'dependencies': [
        '../third_party/libwebsockets/libwebsockets.gyp:*',
      ],
      'sources': [
        'tracker/tracker.cc',
      ],
    }, # target peeracle_tracker
  ], # targets
}
