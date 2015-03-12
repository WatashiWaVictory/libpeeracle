{
  'includes': [
    'build/common.gypi',
  ],
  'variables': {
    'pkg-config': 'pkg-config',
  },
  'conditions': [
    ['OS=="linux" or OS=="android"', {
      'targets': [
        {
          'target_name': 'libpeeracle_so',
          'type': 'shared_library',
          'dependencies': [
            'peeracle',
          ],
          'sources': [
            'java/jni/peeracle_jni.cc'
          ],
          'conditions': [
            ['OS=="linux"', {
              'defines': [
                'HAVE_GTK',
              ],
              'include_dirs': [
                '<(java_home)/include',
                '<(java_home)/include/linux',
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
        {
          'target_name': 'libpeeracle_jar',
          'type': 'none',
          'actions': [
            {
              'variables': {
                'java_src_dir': 'java/src',
                'webrtc_modules_dir': '<(webrtc_root)/modules',
                'build_jar_log': '<(INTERMEDIATE_DIR)/build_jar.log',
                'peeracle_java_files': [
                  'java/src/org/peeracle/Peer.java',
                 ],
                # TODO(fischman): extract this into a webrtc gyp var that can be
                # included here, or better yet, build a proper .jar in webrtc
                # and include it here.
                'android_java_files': [
                ],
              },
              'action_name': 'create_jar',
              'inputs': [
                'build/build_jar.sh',
                '<@(java_files)',
              ],
              'outputs': [
                '<(PRODUCT_DIR)/libpeeracle.jar',
              ],
              'conditions': [
                ['OS=="android"', {
                  'variables': {
                    'java_files': ['<@(peeracle_java_files)', '<@(android_java_files)'],
                    'build_classpath': '<(java_src_dir):<(DEPTH)/third_party/android_tools/sdk/platforms/android-<(android_sdk_version)/android.jar',
                  },
                }, {
                  'variables': {
                    'java_files': ['<@(peeracle_java_files)'],
                    'build_classpath': '<(java_src_dir)',
                  },
                }],
              ],
              'action': [
                'bash', '-ec',
                'mkdir -p <(INTERMEDIATE_DIR) && '
                '{ build/build_jar.sh <(java_home) <@(_outputs) '
                '      <(INTERMEDIATE_DIR)/build_jar.tmp '
                '      <(build_classpath) <@(java_files) '
                '      > <(build_jar_log) 2>&1 || '
                '  { cat <(build_jar_log) ; exit 1; } }'
              ],
            },
          ],
          'dependencies': [
            'libpeeracle_so',
          ],
        },
      ],
    }],
    ['OS=="android"', {
      'targets': [
        {
          # |libjingle_peerconnection_java| builds a jar file with name
          # libjingle_peerconnection_java.jar using Chromes build system.
          # It includes all Java files needed to setup a PeeerConnection call
          # from Android.
          # TODO(perkj): Consider replacing the use of
          # libjingle_peerconnection_jar with this target everywhere.
          'target_name': 'libpeeracle_java',
          'type': 'none',
          'dependencies': [
            'libpeeracle_so',
          ],
          'variables': {
            'java_in_dir': 'java',
            'webrtc_modules_dir': '<(webrtc_root)/modules',
            'additional_src_dirs' : [
              'app/webrtc/java/android',
              '<(webrtc_modules_dir)/audio_device/android/java/src',
              '<(webrtc_modules_dir)/video_capture/android/java/src',
              '<(webrtc_modules_dir)/video_render/android/java/src',
            ],
          },
          'includes': ['../build/java.gypi'],
        }, # libpeeracle_java
      ]
    }],
  ], # conditions
}
