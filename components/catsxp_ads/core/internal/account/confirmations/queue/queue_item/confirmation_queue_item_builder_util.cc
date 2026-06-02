/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/queue_item/confirmation_queue_item_builder_util.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmations_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/debug/debug_flag_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/random/random_util.h"

namespace catsxp_ads {

namespace {
constexpr base::TimeDelta kDebugInitialBackoffDelay = base::Seconds(5);
}  // namespace

base::TimeDelta RetryProcessingConfirmationAfter() {
  return ShouldDebug() ? kDebugInitialBackoffDelay
                       : RandTimeDeltaWithJitter(
                             kProcessConfirmationInitialBackoffDelay.Get());
}

}  // namespace catsxp_ads
