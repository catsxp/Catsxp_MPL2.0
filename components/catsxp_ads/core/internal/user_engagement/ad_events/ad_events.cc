/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events.h"

#include <utility>

#include "base/containers/span.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events_database_table.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"

namespace catsxp_ads {

void RecordAdEvent(const AdInfo& ad,
                   mojom::ConfirmationType mojom_confirmation_type,
                   AdEventCallback callback) {
  RecordAdEvent(BuildAdEvent(ad, mojom_confirmation_type,
                             /*created_at=*/base::Time::Now()),
                std::move(callback));
}

void RecordAdEvent(const AdEventInfo& ad_event, AdEventCallback callback) {
  database::table::AdEvents database_table;
  database_table.RecordEvent(ad_event, std::move(callback));
}

void PurgeOrphanedAdEvents(mojom::AdType mojom_ad_type,
                           AdEventCallback callback) {
  const database::table::AdEvents database_table;
  database_table.PurgeOrphaned(mojom_ad_type, std::move(callback));
}

void PurgeOrphanedAdEvents(base::span<const std::string> placement_ids,
                           AdEventCallback callback) {
  const database::table::AdEvents database_table;
  database_table.PurgeOrphaned(placement_ids, std::move(callback));
}

}  // namespace catsxp_ads
