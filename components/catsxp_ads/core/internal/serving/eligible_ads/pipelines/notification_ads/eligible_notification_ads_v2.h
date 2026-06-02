/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PIPELINES_NOTIFICATION_ADS_ELIGIBLE_NOTIFICATION_ADS_V2_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PIPELINES_NOTIFICATION_ADS_ELIGIBLE_NOTIFICATION_ADS_V2_H_

#include <cstdint>

#include "base/memory/raw_ref.h"
#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ads_database_table.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/pipelines/notification_ads/eligible_notification_ads_base.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events_database_table.h"
#include "catsxp/components/catsxp_ads/core/public/history/site_history.h"

namespace catsxp_ads {

class AntiTargetingResource;
class CreativeAdRoundRobin;
class SubdivisionTargeting;
struct UserModelInfo;

class EligibleNotificationAdsV2 final : public EligibleNotificationAdsBase {
 public:
  EligibleNotificationAdsV2(
      const SubdivisionTargeting& subdivision_targeting,
      const AntiTargetingResource& anti_targeting_resource,
      CreativeAdRoundRobin& creative_ad_round_robin);

  ~EligibleNotificationAdsV2() override;

  // EligibleNotificationAdsBase:
  void GetForUserModel(
      UserModelInfo user_model,
      EligibleAdsCallback<CreativeNotificationAdList> callback) override;

 private:
  void GetForUserModelCallback(
      UserModelInfo user_model,
      EligibleAdsCallback<CreativeNotificationAdList> callback,
      bool success,
      const AdEventList& ad_events);

  void GetSiteHistory(UserModelInfo user_model,
                      const AdEventList& ad_events,
                      EligibleAdsCallback<CreativeNotificationAdList> callback);
  void GetSiteHistoryCallback(
      UserModelInfo user_model,
      const AdEventList& ad_events,
      EligibleAdsCallback<CreativeNotificationAdList> callback,
      uint64_t trace_id,
      const SiteHistoryList& site_history);

  void GetEligibleAds(UserModelInfo user_model,
                      const AdEventList& ad_events,
                      const SiteHistoryList& site_history,
                      EligibleAdsCallback<CreativeNotificationAdList> callback);
  void GetEligibleAdsCallback(
      const UserModelInfo& user_model,
      const AdEventList& ad_events,
      const SiteHistoryList& site_history,
      EligibleAdsCallback<CreativeNotificationAdList> callback,
      bool success,
      const SegmentList& segments,
      CreativeNotificationAdList creative_ads);

  void FilterAndMaybePredictCreativeAd(
      const UserModelInfo& user_model,
      CreativeNotificationAdList creative_ads,
      const AdEventList& ad_events,
      const SiteHistoryList& site_history,
      EligibleAdsCallback<CreativeNotificationAdList> callback);

  const database::table::CreativeNotificationAds creative_ads_database_table_;

  const database::table::AdEvents ad_events_database_table_;

  // Must outlive `this`. Guaranteed by `NotificationAdServing`, which owns both
  // and declares `creative_ad_round_robin_` before `eligible_ads_`.
  const raw_ref<CreativeAdRoundRobin> creative_ad_round_robin_;

  base::WeakPtrFactory<EligibleNotificationAdsV2> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PIPELINES_NOTIFICATION_ADS_ELIGIBLE_NOTIFICATION_ADS_V2_H_
