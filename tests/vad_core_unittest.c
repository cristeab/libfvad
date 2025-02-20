/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "vad_unittest.h"
#include "../src/vad/vad_core.h"
#include <string.h>

#ifdef TEST_VAD_CORE_INIT
void test_main() {
  // Test WebRtcVad_InitCore().
  VadInstT* self = malloc(sizeof(VadInstT));

  // null pointer test.
  EXPECT_EQ(-1, WebRtcVad_InitCore(nullptr));

  // Verify return = 0 for non-null pointer.
  EXPECT_EQ(0, WebRtcVad_InitCore(self));
  // Verify init_flag is set.
  EXPECT_EQ(42, self->init_flag);

  free(self);
}
#endif // TEST_VAD_CORE_INIT


#ifdef TEST_VAD_CORE_SET_MODE
void test_main() {
  VadInstT* self = malloc(sizeof(VadInstT));

  // TODO(bjornv): Add null pointer check if we take care of it in
  // vad_core.c

  ASSERT_EQ(0, WebRtcVad_InitCore(self));
  // Test WebRtcVad_set_mode_core().
  // Invalid modes should return -1.
  EXPECT_EQ(-1, WebRtcVad_set_mode_core(self, -1));
  EXPECT_EQ(-1, WebRtcVad_set_mode_core(self, 1000));
  // Valid modes should return 0.
  for (size_t j = 0; j < kModesSize; ++j) {
    EXPECT_EQ(0, WebRtcVad_set_mode_core(self, kModes[j]));
  }

  free(self);
}
#endif // TEST_VAD_CORE_SET_MODE


#ifdef TEST_VAD_CORE_CALC_VAD
void test_main() {
  VadInstT* self = malloc(sizeof(VadInstT));
  int16_t speech[kMaxFrameLength];

  // TODO(bjornv): Add null pointer check if we take care of it in
  // vad_core.c

  // Test WebRtcVad_CalcVadXXkhz()
  // Verify that all zeros in gives VAD = 0 out.
  memset(speech, 0, sizeof(speech));
  ASSERT_EQ(0, WebRtcVad_InitCore(self));
  for (size_t j = 0; j < kFrameLengthsSize; ++j) {
    if (ValidRatesAndFrameLengths(8000, kFrameLengths[j])) {
      EXPECT_EQ(0, WebRtcVad_CalcVad8khz(self, speech, kFrameLengths[j]));
    }
    if (ValidRatesAndFrameLengths(16000, kFrameLengths[j])) {
      EXPECT_EQ(0, WebRtcVad_CalcVad16khz(self, speech, kFrameLengths[j]));
    }
    if (ValidRatesAndFrameLengths(32000, kFrameLengths[j])) {
      EXPECT_EQ(0, WebRtcVad_CalcVad32khz(self, speech, kFrameLengths[j]));
    }
    if (ValidRatesAndFrameLengths(48000, kFrameLengths[j])) {
      EXPECT_EQ(0, WebRtcVad_CalcVad48khz(self, speech, kFrameLengths[j]));
    }
  }

  // Construct a speech signal that will trigger the VAD in all modes. It is
  // known that (i * i) will wrap around, but that doesn't matter in this case.
  for (size_t i = 0; i < kMaxFrameLength; ++i) {
    speech[i] = i * i;
  }
  for (size_t j = 0; j < kFrameLengthsSize; ++j) {
    if (ValidRatesAndFrameLengths(8000, kFrameLengths[j])) {
      EXPECT_EQ(1, WebRtcVad_CalcVad8khz(self, speech, kFrameLengths[j]));
    }
    if (ValidRatesAndFrameLengths(16000, kFrameLengths[j])) {
      EXPECT_EQ(1, WebRtcVad_CalcVad16khz(self, speech, kFrameLengths[j]));
    }
    if (ValidRatesAndFrameLengths(32000, kFrameLengths[j])) {
      EXPECT_EQ(1, WebRtcVad_CalcVad32khz(self, speech, kFrameLengths[j]));
    }
    if (ValidRatesAndFrameLengths(48000, kFrameLengths[j])) {
      EXPECT_EQ(1, WebRtcVad_CalcVad48khz(self, speech, kFrameLengths[j]));
    }
  }

  free(self);
}
#endif // TEST_VAD_CORE_CALC_VAD
