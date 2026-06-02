/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PIPELINES_NOTIFICATION_ADS_ELIGIBLE_NOTIFICATION_ADS_FACTORY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PIPELINES_NOTIFICATION_ADS_ELIGIBLE_NOTIFICATION_ADS_FACTORY_H_

#include <memory>

namespace catsxp_ads {

class AntiTargetingResource;
class CreativeAdRoundRobin;
class EligibleNotificationAdsBase;
class SubdivisionTargeting;

class EligibleNotificationAdsFactory final {
 public:
  // This class contains only static methods.
  EligibleNotificationAdsFactory() = delete;
  EligibleNotificationAdsFactory(const EligibleNotificationAdsFactory&) =
      delete;
  EligibleNotificationAdsFactory& operator=(
      const EligibleNotificationAdsFactory&) = delete;

  static std::unique_ptr<EligibleNotificationAdsBase> Build(
      int version,
      const SubdivisionTargeting& subdivision_targeting,
      const AntiTargetingResource& anti_targeting_resource,
      CreativeAdRoundRobin& creative_ad_round_robin);
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PIPELINES_NOTIFICATION_ADS_ELIGIBLE_NOTIFICATION_ADS_FACTORY_H_
