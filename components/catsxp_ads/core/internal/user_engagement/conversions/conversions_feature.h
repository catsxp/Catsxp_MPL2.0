/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_FEATURE_H_

#include <string>

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kConversionsFeature);

inline constexpr base::FeatureParam<int> kConversionResourceVersion{
    &kConversionsFeature, "resource_version", 1};

inline constexpr base::FeatureParam<std::string>
    kHtmlMetaTagConversionIdPattern{
        &kConversionsFeature, "html_meta_tag_id_pattern",
        R"~(<meta.*name="ad-conversion-id".*content="([-a-zA-Z0-9]*)".*>)~"};

// Set to 0 to never cap creative set conversions.
inline constexpr base::FeatureParam<size_t> kCreativeSetConversionCap{
    &kConversionsFeature, "creative_set_conversion_cap", 0};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_FEATURE_H_
