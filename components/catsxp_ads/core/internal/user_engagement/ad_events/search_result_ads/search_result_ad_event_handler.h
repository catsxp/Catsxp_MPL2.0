/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_HANDLER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_HANDLER_H_

#include <string>

#include "base/check_op.h"
#include "base/functional/callback.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events_database_table.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/search_result_ads/search_result_ad_event_handler_delegate.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct DepositInfo;
struct SearchResultAdInfo;

using FireSearchResultAdEventHandlerCallback = base::OnceCallback<void(
    bool success,
    const std::string& placement_id,
    mojom::SearchResultAdEventType mojom_ad_event_type)>;

class SearchResultAdEventHandler final
    : public SearchResultAdEventHandlerDelegate {
 public:
  SearchResultAdEventHandler();

  SearchResultAdEventHandler(const SearchResultAdEventHandler&) = delete;
  SearchResultAdEventHandler& operator=(const SearchResultAdEventHandler&) =
      delete;

  ~SearchResultAdEventHandler() override;

  void SetDelegate(SearchResultAdEventHandlerDelegate* delegate) {
    CHECK_EQ(delegate_, nullptr);
    delegate_ = delegate;
  }

  void FireEvent(mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad,
                 mojom::SearchResultAdEventType mojom_ad_event_type,
                 FireSearchResultAdEventHandlerCallback callback);

 private:
  void MaybeFiredEventCallback(
      mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad,
      FireSearchResultAdEventHandlerCallback callback,
      bool success,
      const std::string& placement_id,
      mojom::SearchResultAdEventType mojom_ad_event_type) const;

  void MaybeFireServedEvent(const SearchResultAdInfo& ad,
                            FireSearchResultAdEventHandlerCallback callback);
  void MaybeFireServedEventCallback(
      const SearchResultAdInfo& ad,
      FireSearchResultAdEventHandlerCallback callback,
      bool success,
      const AdEventList& ad_events);

  void MaybeFireViewedEvent(
      const SearchResultAdInfo& ad,
      const DepositInfo& deposit,
      FireSearchResultAdEventHandlerCallback callback) const;
  void MaybeFireViewedEventCallback(
      const SearchResultAdInfo& ad,
      FireSearchResultAdEventHandlerCallback callback,
      bool success) const;

  void MaybeFireClickedEvent(
      const SearchResultAdInfo& ad,
      FireSearchResultAdEventHandlerCallback callback) const;

  void MaybeFireEvent(const SearchResultAdInfo& ad,
                      mojom::SearchResultAdEventType mojom_ad_event_type,
                      FireSearchResultAdEventHandlerCallback callback) const;
  void MaybeFireEventCallback(
      const SearchResultAdInfo& ad,
      mojom::SearchResultAdEventType mojom_ad_event_type,
      FireSearchResultAdEventHandlerCallback callback,
      bool success,
      const AdEventList& ad_events) const;

  void FireEvent(const SearchResultAdInfo& ad,
                 mojom::SearchResultAdEventType mojom_ad_event_type,
                 FireSearchResultAdEventHandlerCallback callback) const;
  void FireEventCallback(const SearchResultAdInfo& ad,
                         mojom::SearchResultAdEventType mojom_ad_event_type,
                         FireSearchResultAdEventHandlerCallback callback,
                         bool success) const;

  void SuccessfullyFiredEvent(
      const SearchResultAdInfo& ad,
      mojom::SearchResultAdEventType mojom_ad_event_type,
      FireSearchResultAdEventHandlerCallback callback) const;
  void FailedToFireEvent(const SearchResultAdInfo& ad,
                         mojom::SearchResultAdEventType mojom_ad_event_type,
                         FireSearchResultAdEventHandlerCallback callback) const;

  void NotifyWillFireSearchResultAdClickedEvent(
      const SearchResultAdInfo& ad) const;
  void NotifyDidFireSearchResultAdEvent(
      const SearchResultAdInfo& ad,
      mojom::SearchResultAdEventType mojom_ad_event_type) const;
  void NotifyFailedToFireSearchResultAdEvent(
      const SearchResultAdInfo& ad,
      mojom::SearchResultAdEventType mojom_ad_event_type) const;

  raw_ptr<SearchResultAdEventHandlerDelegate> delegate_ =
      nullptr;  // Not owned.

  const database::table::AdEvents ad_events_database_table_;

  base::WeakPtrFactory<SearchResultAdEventHandler> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_SEARCH_RESULT_ADS_SEARCH_RESULT_AD_EVENT_HANDLER_H_
