/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events_database_util.h"

#include "base/functional/bind.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events_database_table.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::database {

void PurgeAdEventsForType(mojom::AdType ad_type) {
  const table::AdEvents database_table;
  database_table.PurgeForAdType(
      ad_type, base::BindOnce(
                   [](mojom::AdType ad_type, bool success) {
                     if (!success) {
                       return BLOG(
                           0, "Failed to purge " << ad_type << " ad events");
                     }

                     BLOG(3, "Successfully purged " << ad_type << " ad events");
                   },
                   ad_type));
}

void PurgeExpiredAdEvents() {
  const table::AdEvents database_table;
  database_table.PurgeExpired(base::BindOnce([](bool success) {
    if (!success) {
      return BLOG(0, "Failed to purge expired ad events");
    }

    BLOG(3, "Successfully purged expired ad events");
  }));
}

void PurgeAllOrphanedAdEvents() {
  const table::AdEvents database_table;
  database_table.PurgeAllOrphaned(base::BindOnce([](bool success) {
    if (!success) {
      return BLOG(0, "Failed to purge all orphaned ad events");
    }

    BLOG(3, "Successfully purged all orphaned ad events");
  }));
}

}  // namespace catsxp_ads::database
