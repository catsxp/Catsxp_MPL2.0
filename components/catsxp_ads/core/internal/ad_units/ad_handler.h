/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_AD_HANDLER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_AD_HANDLER_H_

#include <cstdint>
#include <string>

#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/creative_ad_cache.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/new_tab_page_ad/new_tab_page_ad_handler.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/notification_ad/notification_ad_handler.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_handler.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_resource.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/subdivision.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/anti_targeting/resource/anti_targeting_resource.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_processor.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_resource.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/resource/text_classification_resource.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/text_classification_processor.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/geographical/subdivision/subdivision_targeting.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions_observer.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/site_visit/site_visit.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/site_visit/site_visit_observer.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads {

class SiteVisit;
struct AdInfo;
struct ConversionInfo;

class AdHandler final : public ConversionsObserver, SiteVisitObserver {
 public:
  AdHandler();

  AdHandler(const AdHandler&) = delete;
  AdHandler& operator=(const AdHandler&) = delete;

  ~AdHandler() override;

  void ParseAndSaveNewTabPageAds(base::DictValue dict, ResultCallback callback);
  void MaybeServeNewTabPageAd(MaybeServeNewTabPageAdCallback callback);
  void TriggerNewTabPageAdEvent(
      const std::string& placement_id,
      const std::string& creative_instance_id,
      mojom::NewTabPageAdEventType mojom_ad_event_type,
      ResultCallback callback);

  void TriggerNotificationAdEvent(
      const std::string& placement_id,
      mojom::NotificationAdEventType mojom_ad_event_type,
      ResultCallback callback);

  std::optional<mojom::CreativeSearchResultAdInfoPtr> MaybeGetSearchResultAd(
      const std::string& placement_id);

  void TriggerSearchResultAdEvent(
      mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad,
      mojom::SearchResultAdEventType mojom_ad_event_type,
      ResultCallback callback);

 private:
  // ConversionsObserver:
  void OnDidConvertAd(const ConversionInfo& conversion) override;

  // SiteVisitObserver:
  void OnMaybeLandOnPage(const AdInfo& ad, base::TimeDelta after) override;
  void OnDidSuspendPageLand(int32_t tab_id,
                            base::TimeDelta remaining_time) override;
  void OnDidResumePageLand(int32_t tab_id,
                           base::TimeDelta remaining_time) override;
  void OnDidLandOnPage(int32_t tab_id,
                       int32_t http_response_code,
                       const AdInfo& ad) override;
  void OnDidNotLandOnPage(int32_t tab_id, const AdInfo& ad) override;
  void OnCanceledPageLand(int32_t tab_id, const AdInfo& ad) override;

  CatalogResource catalog_resource_;

  CreativeAdCache creative_ad_cache_;

  Conversions conversions_;
  base::ScopedObservation<Conversions, ConversionsObserver>
      conversions_observation_{this};

  SiteVisit site_visit_;
  base::ScopedObservation<SiteVisit, SiteVisitObserver> site_visit_observation_{
      this};

  SubdivisionTargeting subdivision_targeting_;
  Subdivision subdivision_;
  base::ScopedObservation<Subdivision, SubdivisionObserver>
      subdivision_observation_{&subdivision_targeting_};

  AntiTargetingResource anti_targeting_resource_;

  PurchaseIntentResource purchase_intent_resource_;
  PurchaseIntentProcessor purchase_intent_processor_;

  TextClassificationResource text_classification_resource_;
  TextClassificationProcessor text_classification_processor_;

  NewTabPageAdHandler new_tab_page_ad_handler_;
  NotificationAdHandler notification_ad_handler_;
  SearchResultAdHandler search_result_ad_handler_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_AD_HANDLER_H_
