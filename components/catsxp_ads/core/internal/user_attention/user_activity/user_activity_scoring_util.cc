/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_scoring_util.h"

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_event_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_scoring.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_trigger_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_util.h"

namespace catsxp_ads {

bool WasUserActive() {
  const UserActivityTriggerList triggers =
      ToUserActivityTriggers(kUserActivityTriggers.Get());

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          kUserActivityTimeWindow.Get());

  return GetUserActivityScore(triggers, events) >= kUserActivityThreshold.Get();
}

}  // namespace catsxp_ads
