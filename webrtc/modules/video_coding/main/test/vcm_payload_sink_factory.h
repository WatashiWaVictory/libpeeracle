/*
 *  Copyright (c) 2013 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include <string>
#include <vector>

#include "webrtc/base/constructormagic.h"
#include "webrtc/modules/video_coding/main/interface/video_coding_defines.h"
#include "webrtc/modules/video_coding/main/test/rtp_player.h"
#include "webrtc/system_wrappers/interface/scoped_ptr.h"

class NullEventFactory;

namespace webrtc {
class Clock;
class CriticalSectionWrapper;

namespace rtpplayer {
class VcmPayloadSinkFactory : public PayloadSinkFactoryInterface {
 public:
  VcmPayloadSinkFactory(const std::string& base_out_filename,
                        Clock* clock, bool protection_enabled,
                        VCMVideoProtection protection_method,
                        int64_t rtt_ms, uint32_t render_delay_ms,
                        uint32_t min_playout_delay_ms);
  virtual ~VcmPayloadSinkFactory();

  // PayloadSinkFactoryInterface
  virtual PayloadSinkInterface* Create(RtpStreamInterface* stream);

  int DecodeAndProcessAll(bool decode_dual_frame);
  bool ProcessAll();
  bool DecodeAll();

 private:
  class VcmPayloadSink;
  friend class VcmPayloadSink;
  typedef std::vector<VcmPayloadSink*> Sinks;

  void Remove(VcmPayloadSink* sink);

  std::string base_out_filename_;
  Clock* clock_;
  bool protection_enabled_;
  VCMVideoProtection protection_method_;
  int64_t rtt_ms_;
  uint32_t render_delay_ms_;
  uint32_t min_playout_delay_ms_;
  scoped_ptr<NullEventFactory> null_event_factory_;
  scoped_ptr<CriticalSectionWrapper> crit_sect_;
  Sinks sinks_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(VcmPayloadSinkFactory);
};
}  // namespace rtpplayer
}  // namespace webrtc
