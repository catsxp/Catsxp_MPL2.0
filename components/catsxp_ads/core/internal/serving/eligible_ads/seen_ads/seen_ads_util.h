/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_SEEN_ADS_SEEN_ADS_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_SEEN_ADS_SEEN_ADS_UTIL_H_

#include <optional>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"

namespace base {
class Time;
}  // namespace base

namespace catsxp_ads {

std::optional<base::Time> GetLastSeenAdAt(
    const AdEventList& ad_events,
    const std::string& creative_instance_id);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_SEEN_ADS_SEEN_ADS_UTIL_H_
