/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_SERVICE_TEST_ADS_SERVICE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_SERVICE_TEST_ADS_SERVICE_MOCK_H_

#include <cstdint>
#include <string>
#include <vector>

#include "catsxp/components/catsxp_ads/core/browser/service/ads_service.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class AdsServiceMock : public AdsService {
 public:
  AdsServiceMock();

  AdsServiceMock(const AdsServiceMock&) = delete;
  AdsServiceMock& operator=(const AdsServiceMock&) = delete;

  ~AdsServiceMock() override;

  MOCK_METHOD(void,
              AddBatAdsObserver,
              (mojo::PendingRemote<bat_ads::mojom::BatAdsObserver>));

  MOCK_METHOD(bool, IsIneligibleToStart, (), (const));
  MOCK_METHOD(bool, IsInitialized, (), (const));

  MOCK_METHOD(bool, IsBrowserUpgradeRequiredToServeAds, (), (const));

  MOCK_METHOD(int64_t, GetMaximumNotificationAdsPerHour, (), (const));

  MOCK_METHOD(void, OnNotificationAdShown, (const std::string&));
  MOCK_METHOD(void, OnNotificationAdClosed, (const std::string&, bool));
  MOCK_METHOD(void, OnNotificationAdClicked, (const std::string&));

  MOCK_METHOD(void, GetInternals, (GetInternalsCallback));

  MOCK_METHOD(void, GetDiagnostics, (GetDiagnosticsCallback));

  MOCK_METHOD(void, GetStatementOfAccounts, (GetStatementOfAccountsCallback));

  MOCK_METHOD(void,
              ParseAndSaveNewTabPageAds,
              (base::DictValue, ResultCallback));
  MOCK_METHOD(void,
              MaybeServeNewTabPageAd,
              (MaybeServeMojomNewTabPageAdCallback));
  MOCK_METHOD(void,
              TriggerNewTabPageAdEvent,
              (const std::string&,
               const std::string&,
               mojom::NewTabPageAdMetricType,
               mojom::NewTabPageAdEventType,
               ResultCallback));

  MOCK_METHOD(void,
              MaybeGetSearchResultAd,
              (const std::string&, MaybeGetSearchResultAdCallback));
  MOCK_METHOD(void,
              TriggerSearchResultAdEvent,
              (mojom::CreativeSearchResultAdInfoPtr,
               mojom::SearchResultAdEventType,
               ResultCallback));

  MOCK_METHOD(void,
              PurgeOrphanedAdEventsForType,
              (mojom::AdType, ResultCallback));

  MOCK_METHOD(void,
              GetAdHistory,
              (base::Time, base::Time, GetAdHistoryForUICallback));

  MOCK_METHOD(void, ClearData, (ResultCallback));

  MOCK_METHOD(void, ToggleLikeAd, (mojom::ReactionInfoPtr, ResultCallback));
  MOCK_METHOD(void, ToggleDislikeAd, (mojom::ReactionInfoPtr, ResultCallback));
  MOCK_METHOD(void,
              ToggleLikeSegment,
              (mojom::ReactionInfoPtr, ResultCallback));
  MOCK_METHOD(void,
              ToggleDislikeSegment,
              (mojom::ReactionInfoPtr, ResultCallback));
  MOCK_METHOD(void, ToggleSaveAd, (mojom::ReactionInfoPtr, ResultCallback));
  MOCK_METHOD(void,
              ToggleMarkAdAsInappropriate,
              (mojom::ReactionInfoPtr, ResultCallback));

  MOCK_METHOD(void,
              NotifyTabTextContentDidChange,
              (int32_t, const std::vector<GURL>&, const std::string&));
  MOCK_METHOD(void, NotifyTabDidStartPlayingMedia, (int32_t));
  MOCK_METHOD(void, NotifyTabDidStopPlayingMedia, (int32_t));
  MOCK_METHOD(void,
              NotifyTabDidChange,
              (int32_t, const std::vector<GURL>&, bool, bool, bool));
  MOCK_METHOD(void, NotifyTabDidLoad, (int32_t, int));
  MOCK_METHOD(void, NotifyDidCloseTab, (int32_t));
  MOCK_METHOD(void, NotifyUserGestureEventTriggered, (int32_t));
  MOCK_METHOD(void, NotifyBrowserDidBecomeActive, ());
  MOCK_METHOD(void, NotifyBrowserDidResignActive, ());

  MOCK_METHOD(void, NotifyDidSolveAdaptiveCaptcha, ());
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_SERVICE_TEST_ADS_SERVICE_MOCK_H_
