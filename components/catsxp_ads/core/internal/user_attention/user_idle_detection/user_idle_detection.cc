/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_idle_detection/user_idle_detection.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/last_unidle_time_diagnostic_entry_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client.h"

namespace catsxp_ads {

UserIdleDetection::UserIdleDetection() {
  ads_client_observation_.Observe(&GetAdsClient());
}

UserIdleDetection::~UserIdleDetection() = default;

///////////////////////////////////////////////////////////////////////////////

void UserIdleDetection::OnNotifyUserDidBecomeActive(base::TimeDelta idle_time,
                                                    bool screen_was_locked) {
  if (!UserHasJoinedCatsxpRewards()) {
    // User has not joined Catsxp Rewards, so we don't need to track idle time.
    return;
  }

  BLOG(1, "User is active after " << idle_time);
  if (screen_was_locked) {
    BLOG(1, "Screen was locked before the user become active");
  }

  SetLastUnIdleTimeDiagnosticEntry(base::Time::Now());
}

void UserIdleDetection::OnNotifyUserDidBecomeIdle() {
  if (!UserHasJoinedCatsxpRewards()) {
    // User has not joined Catsxp Rewards, so we don't need to track idle time.
    return;
  }

  BLOG(1, "User is idle");
}

}  // namespace catsxp_ads
