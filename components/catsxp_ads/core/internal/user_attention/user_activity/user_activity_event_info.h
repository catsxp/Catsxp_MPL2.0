/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_EVENT_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_EVENT_INFO_H_

#include "base/containers/circular_deque.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_event_types.h"

namespace catsxp_ads {

struct UserActivityEventInfo final {
  bool operator==(const UserActivityEventInfo&) const = default;

  UserActivityEventType type;
  base::Time created_at;
};

using UserActivityEventList = base::circular_deque<UserActivityEventInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_EVENT_INFO_H_
