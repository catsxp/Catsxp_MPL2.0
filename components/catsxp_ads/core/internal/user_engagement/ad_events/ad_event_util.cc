/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_util.h"

#include "base/time/time.h"

namespace catsxp_ads {

std::vector<base::Time> ToHistory(const AdEventList& ad_events) {
  std::vector<base::Time> history;
  history.reserve(ad_events.size());

  for (const auto& ad_event : ad_events) {
    if (ad_event.IsValid()) {
      history.push_back(*ad_event.created_at);
    }
  }

  return history;
}

}  // namespace catsxp_ads
