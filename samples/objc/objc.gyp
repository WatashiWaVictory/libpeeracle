#
# Copyright (c) 2015 peeracle contributors
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

{
  'includes': [
    '../../build/common.gypi'
  ],
  'targets': [
    {
      'target_name': 'PeeracleDemo',
      'type': 'executable',
      'product_name': 'PeeracleDemo',
      'mac_bundle': 1,
      'dependencies': [
        '../../objc/peeracle_objc.gyp:*',
      ],
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
      },
      'conditions': [
        ['OS=="ios"', {
          'cflags': [
            '-fPIC',
          ],
          'dependencies': [
            '<(DEPTH)/third_party/webrtc/chromium/src/third_party/ffmpeg/ffmpeg.gyp:ffmpeg',
          ],
          'mac_bundle_resources': [
            'ios/kxmovie/kxmovie.bundle/music_icon.png'
          ],
          'include_dirs': [
            'ios/kxmovie'
          ],
          'sources': [
            'ios/AppDelegate.h',
            'ios/AppDelegate.m',
            'ios/main.m',
            'ios/MainViewController.h',
            'ios/MainViewController.m',

            'ios/kxmovie/KxAudioManager.h',
            'ios/kxmovie/KxAudioManager.m',
            'ios/kxmovie/KxLogger.h',
            'ios/kxmovie/KxMovieDecoder.h',
            'ios/kxmovie/KxMovieDecoder.m',
            'ios/kxmovie/KxMovieGLView.h',
            'ios/kxmovie/KxMovieGLView.m',
            'ios/kxmovie/KxMovieViewController.h',
            'ios/kxmovie/KxMovieViewController.m',
          ],
          'xcode_settings': {
            'INFOPLIST_FILE': 'ios/Info.plist',
            'OTHER_LDFLAGS': [
              '-framework Accelerate',
              '-framework AVFoundation',
              '-liconv'
            ],
          },
        }],
        ['OS=="mac"', {
          'sources': [
            'mac/main.m',
          ],
          'xcode_settings': {
            'CLANG_WARN_OBJC_MISSING_PROPERTY_SYNTHESIS': 'NO',
            'INFOPLIST_FILE': 'mac/Info.plist',
            'MACOSX_DEPLOYMENT_TARGET' : '10.8',
            'OTHER_LDFLAGS': [
              '-framework AVFoundation',
            ],
          },
        }],
        ['target_arch=="ia32"', {
          'dependencies' : [
            '<(webrtc_depth)/testing/iossim/iossim.gyp:iossim#host',
          ],
        }],
      ],
    },
  ],
}
