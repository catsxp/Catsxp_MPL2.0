/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PIPELINES_NEW_TAB_PAGE_ADS_ELIGIBLE_NEW_TAB_PAGE_ADS_FACTORY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PIPELINES_NEW_TAB_PAGE_ADS_ELIGIBLE_NEW_TAB_PAGE_ADS_FACTORY_H_

#include <memory>

namespace catsxp_ads {

class AntiTargetingResource;
class CreativeAdRoundRobin;
class EligibleNewTabPageAdsBase;
class SubdivisionTargeting;

class EligibleAdsFactory final {
 public:
  // This class contains only static methods.
  EligibleAdsFactory() = delete;
  EligibleAdsFactory(const EligibleAdsFactory&) = delete;
  EligibleAdsFactory& operator=(const EligibleAdsFactory&) = delete;

  static std::unique_ptr<EligibleNewTabPageAdsBase> Build(
      int version,
      const SubdivisionTargeting& subdivision_targeting,
      const AntiTargetingResource& anti_targeting_resource,
      CreativeAdRoundRobin& creative_ad_round_robin);
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PIPELINES_NEW_TAB_PAGE_ADS_ELIGIBLE_NEW_TAB_PAGE_ADS_FACTORY_H_
