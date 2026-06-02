/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULE_UTIL_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

struct CreativeAdInfo;

bool DoesRespectCampaignCap(const CreativeAdInfo& creative_ad,
                            const AdEventList& ad_events,
                            mojom::ConfirmationType mojom_confirmation_type,
                            base::TimeDelta time_constraint,
                            size_t cap);
bool DoesRespectCampaignCap(const CreativeAdInfo& creative_ad,
                            const AdEventList& ad_events,
                            mojom::ConfirmationType mojom_confirmation_type,
                            size_t cap);

bool DoesRespectCreativeSetCap(const CreativeAdInfo& creative_ad,
                               const AdEventList& ad_events,
                               mojom::ConfirmationType mojom_confirmation_type,
                               base::TimeDelta time_constraint,
                               size_t cap);
bool DoesRespectCreativeSetCap(const CreativeAdInfo& creative_ad,
                               const AdEventList& ad_events,
                               mojom::ConfirmationType mojom_confirmation_type,
                               size_t cap);

bool DoesRespectCreativeCap(const CreativeAdInfo& creative_ad,
                            const AdEventList& ad_events,
                            mojom::ConfirmationType mojom_confirmation_type,
                            base::TimeDelta time_constraint,
                            size_t cap);
bool DoesRespectCreativeCap(const CreativeAdInfo& creative_ad,
                            const AdEventList& ad_events,
                            mojom::ConfirmationType mojom_confirmation_type,
                            size_t cap);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_EXCLUSION_RULES_EXCLUSION_RULE_UTIL_H_
