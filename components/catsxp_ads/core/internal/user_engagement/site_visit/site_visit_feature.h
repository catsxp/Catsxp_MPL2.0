/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_SITE_VISIT_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_SITE_VISIT_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kSiteVisitFeature);

inline constexpr base::FeatureParam<base::TimeDelta> kPageLandAfter{
    &kSiteVisitFeature, "page_land_after", base::Seconds(5)};

// Set to 0 to never cap.
inline constexpr base::FeatureParam<size_t> kPageLandCap{&kSiteVisitFeature,
                                                         "page_land_cap", 0};

inline constexpr base::FeatureParam<bool> kShouldSuspendAndResumePageLand{
    &kSiteVisitFeature, "should_suspend_and_resume_page_land", true};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_SITE_VISIT_FEATURE_H_
