/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/pipelines/notification_ads/eligible_notification_ads_factory.h"

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/pipelines/notification_ads/eligible_notification_ads_base.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/pipelines/notification_ads/eligible_notification_ads_v2.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/round_robin/creative_ad_round_robin.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/anti_targeting/resource/anti_targeting_resource.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/geographical/subdivision/subdivision_targeting.h"

namespace catsxp_ads {

std::unique_ptr<EligibleNotificationAdsBase>
EligibleNotificationAdsFactory::Build(
    int version,
    const SubdivisionTargeting& subdivision_targeting,
    const AntiTargetingResource& anti_targeting_resource,
    CreativeAdRoundRobin& creative_ad_round_robin) {
  switch (version) {
    case 2: {
      return std::make_unique<EligibleNotificationAdsV2>(
          subdivision_targeting, anti_targeting_resource,
          creative_ad_round_robin);
    }

    default: {
      return nullptr;
    }
  }
}

}  // namespace catsxp_ads
