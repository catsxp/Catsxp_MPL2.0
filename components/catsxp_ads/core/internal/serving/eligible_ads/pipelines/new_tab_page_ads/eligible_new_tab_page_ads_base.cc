/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/pipelines/new_tab_page_ads/eligible_new_tab_page_ads_base.h"

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/anti_targeting/resource/anti_targeting_resource.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/geographical/subdivision/subdivision_targeting.h"

namespace catsxp_ads {

EligibleNewTabPageAdsBase::EligibleNewTabPageAdsBase(
    const SubdivisionTargeting& subdivision_targeting,
    const AntiTargetingResource& anti_targeting_resource)
    : subdivision_targeting_(subdivision_targeting),
      anti_targeting_resource_(anti_targeting_resource) {}

EligibleNewTabPageAdsBase::~EligibleNewTabPageAdsBase() = default;

}  // namespace catsxp_ads
