/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_TRIGGER_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_TRIGGER_INFO_H_

#include <string>
#include <vector>

namespace catsxp_ads {

struct UserActivityTriggerInfo final {
  bool operator==(const UserActivityTriggerInfo&) const = default;

  std::string event_sequence;
  double score = 0.0;
};

using UserActivityTriggerList = std::vector<UserActivityTriggerInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_TRIGGER_INFO_H_
