/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/seen_ads/seen_ads_util.h"

#include <algorithm>

#include "base/time/time.h"

namespace catsxp_ads {

std::optional<base::Time> GetLastSeenAdAt(
    const AdEventList& ad_events,
    const std::string& creative_instance_id) {
  const auto iter = std::ranges::find_if(
      ad_events, [&creative_instance_id](const AdEventInfo& ad_event) {
        return ad_event.confirmation_type ==
                   mojom::ConfirmationType::kViewedImpression &&
               ad_event.creative_instance_id == creative_instance_id;
      });

  if (iter == ad_events.cend()) {
    return std::nullopt;
  }

  return iter->created_at;
}

}  // namespace catsxp_ads
