/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_UTIL_H_

#include <cstddef>
#include <string>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_event_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_event_types.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_trigger_info.h"

namespace catsxp_ads {

size_t GetNumberOfUserActivityEvents(const UserActivityEventList& events,
                                     UserActivityEventType event_type);
base::TimeDelta GetTimeSinceLastUserActivityEvent(
    const UserActivityEventList& events,
    UserActivityEventType event_type);

UserActivityTriggerList ToUserActivityTriggers(const std::string& param_value);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_UTIL_H_
