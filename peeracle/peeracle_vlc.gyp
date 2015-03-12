{
  'includes': [
    'build/common.gypi',
  ],
  'variables': {
    'pkg-config': 'pkg-config',
  },
  'targets': [
    {
      'target_name': 'peeracle_plugin',
      'type': 'shared_library',
      'dependencies': [
        'peeracle.gyp:peeracle_peer',
        'peeracle.gyp:peeracle_tracker',
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
    }, # target peeracle_plugin
  ], # targets
}