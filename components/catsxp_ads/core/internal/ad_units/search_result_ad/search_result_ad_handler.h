/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_HANDLER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_HANDLER_H_

#include <string>

#include "base/containers/circular_deque.h"
#include "base/memory/raw_ref.h"
#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/search_result_ads/search_result_ad_event_handler.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/search_result_ads/search_result_ad_event_handler_delegate.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads {

class SiteVisit;
struct SearchResultAdInfo;

class SearchResultAdHandler final : public SearchResultAdEventHandlerDelegate {
 public:
  explicit SearchResultAdHandler(SiteVisit& site_visit);

  SearchResultAdHandler(const SearchResultAdHandler&) = delete;
  SearchResultAdHandler& operator=(const SearchResultAdHandler&) = delete;

  ~SearchResultAdHandler() override;

  static void DeferTriggeringAdViewedEventForTesting();

  // You must call this if `DeferTriggeringAdViewedEventForTesting` is called.
  static void TriggerDeferredAdViewedEventForTesting();

  void TriggerEvent(mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad,
                    mojom::SearchResultAdEventType mojom_ad_event_type,
                    ResultCallback callback);

 private:
  void FireServedEventCallback(
      mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad,
      ResultCallback callback,
      bool success,
      const std::string& placement_id,
      mojom::SearchResultAdEventType mojom_ad_event_type);

  void MaybeTriggerDeferredAdViewedEvent(ResultCallback callback);
  void FireAdViewedEventCallback(
      ResultCallback callback,
      bool success,
      const std::string& placement_id,
      mojom::SearchResultAdEventType mojom_ad_event_type);

  // SearchResultAdEventHandlerDelegate:
  void OnWillFireSearchResultAdClickedEvent(
      const SearchResultAdInfo& ad) override;
  void OnDidFireSearchResultAdServedEvent(
      const SearchResultAdInfo& ad) override;
  void OnDidFireSearchResultAdViewedEvent(
      const SearchResultAdInfo& ad) override;
  void OnDidFireSearchResultAdClickedEvent(
      const SearchResultAdInfo& ad) override;

  const raw_ref<SiteVisit> site_visit_;

  SearchResultAdEventHandler event_handler_;

  bool is_processing_viewed_ad_event_queue_ = false;
  base::circular_deque<mojom::CreativeSearchResultAdInfoPtr>
      viewed_ad_event_queue_;

  base::WeakPtrFactory<SearchResultAdHandler> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_HANDLER_H_
