/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_util.h"

#include <algorithm>
#include <vector>

#include "base/containers/adapters.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_split.h"
#include "base/strings/string_util.h"
#include "base/time/time.h"

namespace catsxp_ads {

size_t GetNumberOfUserActivityEvents(const UserActivityEventList& events,
                                     UserActivityEventType event_type) {
  return std::ranges::count_if(
      events, [event_type](const UserActivityEventInfo& event) {
        return event.type == event_type;
      });
}

base::TimeDelta GetTimeSinceLastUserActivityEvent(
    const UserActivityEventList& events,
    UserActivityEventType event_type) {
  const auto iter = std::ranges::find(base::Reversed(events), event_type,
                                      &UserActivityEventInfo::type);
  if (iter == events.crend()) {
    return {};
  }

  return base::Time::Now() - iter->created_at;
}

UserActivityTriggerList ToUserActivityTriggers(const std::string& param_value) {
  const std::vector<std::string> components = base::SplitString(
      param_value, ";", base::TRIM_WHITESPACE, base::SPLIT_WANT_NONEMPTY);

  UserActivityTriggerList triggers;
  triggers.reserve(components.size());

  for (const auto& component : components) {
    const std::vector<std::string> value = base::SplitString(
        component, "=", base::TRIM_WHITESPACE, base::SPLIT_WANT_NONEMPTY);
    if (value.size() != 2) {
      continue;
    }

    const std::string& event_sequence = value.at(0);
    if (event_sequence.length() % 2 != 0) {
      continue;
    }

    UserActivityTriggerInfo trigger;
    trigger.event_sequence = base::ToUpperASCII(event_sequence);
    if (!base::StringToDouble(value.at(1), &trigger.score)) {
      continue;
    }

    triggers.push_back(trigger);
  }

  return triggers;
}

}  // namespace catsxp_ads
