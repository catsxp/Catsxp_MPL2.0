/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_SCORING_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_SCORING_H_

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_event_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_trigger_info.h"

namespace catsxp_ads {

double GetUserActivityScore(const UserActivityTriggerList& triggers,
                            const UserActivityEventList& events);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_SCORING_H_
