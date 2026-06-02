/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENTS_DATABASE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENTS_DATABASE_UTIL_H_

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::database {

void PurgeAdEventsForType(mojom::AdType ad_type);

void PurgeExpiredAdEvents();

void PurgeAllOrphanedAdEvents();

}  // namespace catsxp_ads::database

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENTS_DATABASE_UTIL_H_
