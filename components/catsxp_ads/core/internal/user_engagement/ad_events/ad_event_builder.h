/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_BUILDER_H_

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace base {
class Time;
}  // namespace base

namespace catsxp_ads {

struct AdEventInfo;
struct AdInfo;

// Builds a new `AdEventInfo` for the given `ad`, `mojom_confirmation_type`, and
// `created_at` time.
AdEventInfo BuildAdEvent(const AdInfo& ad,
                         mojom::ConfirmationType mojom_confirmation_type,
                         base::Time created_at);

// Rebuilds an existing `AdEventInfo` with a new `mojom_confirmation_type` and
// `created_at` time.
AdEventInfo RebuildAdEvent(const AdEventInfo& ad_event,
                           mojom::ConfirmationType mojom_confirmation_type,
                           base::Time created_at);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_BUILDER_H_
