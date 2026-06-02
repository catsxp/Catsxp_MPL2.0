/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kAdEventFeature);

// Set to 0 to always deduplicate viewed ad events.
inline constexpr base::FeatureParam<base::TimeDelta>
    kDeduplicateViewedAdEventFor{
        &kAdEventFeature, "deduplicate_viewed_ad_event_for", base::Seconds(0)};

// Set to 0 to always deduplicate clicked ad events.
inline constexpr base::FeatureParam<base::TimeDelta>
    kDeduplicateClickedAdEventFor{
        &kAdEventFeature, "deduplicate_clicked_ad_event_for", base::Seconds(1)};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_FEATURE_H_
