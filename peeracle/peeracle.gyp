{
  'includes': [
    'build/common.gypi',
  ],
  'variables': {
    'pkg-config': 'pkg-config',
  },
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
    {
      'target_name': 'peeracle_plugin',
      'type': 'shared_library',
      'dependencies': [
        'peeracle.gyp:peeracle',
      ],
      'sources': [
        'plugin/access.cc',
        'plugin/module.cc',
      ],
      'conditions': [
        ['OS=="linux"', {
          'defines': [
            'HAVE_GTK',
          ],
          'cflags': [
            '<!@(<(pkg-config) --cflags vlc-plugin)',
          ],
          'ldflags': [
            '<!@(<(pkg-config) --libs-only-L --libs-only-other vlc-plugin)',
          ],
          'libraries': [
            '<!@(<(pkg-config) --libs-only-l vlc-plugin)',
          ],
          'include_dirs': [
            '<(java_home)/include',
            '<(java_home)/include/linux',
            '../third_party/vlc/',
          ],
          'link_settings': {
            'libraries': [
              '<!@(pkg-config --libs-only-l gobject-2.0 gthread-2.0'
                  ' gtk+-2.0)',
            ],
          },
        }],
      ],
    },
  ],
}
