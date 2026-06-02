/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_CLIENT_TEST_ADS_CLIENT_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_CLIENT_TEST_ADS_CLIENT_MOCK_H_

#include <optional>
#include <string>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_callback.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class AdsClientMock : public AdsClient {
 public:
  AdsClientMock();

  AdsClientMock(const AdsClientMock&) = delete;
  AdsClientMock& operator=(const AdsClientMock&) = delete;

  ~AdsClientMock() override;

  MOCK_METHOD(void, AddObserver, (AdsClientNotifierObserver*));
  MOCK_METHOD(void, RemoveObserver, (AdsClientNotifierObserver*));
  MOCK_METHOD(void, NotifyPendingObservers, ());

  MOCK_METHOD(bool, IsNetworkConnectionAvailable, (), (const));

  MOCK_METHOD(bool, IsBrowserActive, (), (const));
  MOCK_METHOD(bool, IsBrowserInFullScreenMode, (), (const));

  MOCK_METHOD(bool, CanShowNotificationAds, (), (const));
  MOCK_METHOD(bool,
              CanShowNotificationAdsWhileBrowserIsBackgrounded,
              (),
              (const));
  MOCK_METHOD(void, ShowNotificationAd, (const NotificationAdInfo&));
  MOCK_METHOD(void, CloseNotificationAd, (const std::string&));

  MOCK_METHOD(void, GetSiteHistory, (int, int, GetSiteHistoryCallback));

  MOCK_METHOD(void, UrlRequest, (mojom::UrlRequestInfoPtr, UrlRequestCallback));

  MOCK_METHOD(void,
              Save,
              (const std::string&, const std::string&, ResultCallback));
  MOCK_METHOD(void, Remove, (const std::string&, ResultCallback));
  MOCK_METHOD(void, Load, (const std::string&, LoadCallback));

  MOCK_METHOD(void,
              LoadResourceComponent,
              (const std::string&, int, LoadFileCallback));

  MOCK_METHOD(void,
              ShowScheduledCaptcha,
              (const std::string&, const std::string&));

  MOCK_METHOD(bool, FindProfilePref, (const std::string&), (const));
  MOCK_METHOD(std::optional<base::Value>, GetProfilePref, (const std::string&));
  MOCK_METHOD(void, SetProfilePref, (const std::string&, base::Value));
  MOCK_METHOD(void, ClearProfilePref, (const std::string&));
  MOCK_METHOD(bool, HasProfilePrefPath, (const std::string&), (const));

  MOCK_METHOD(bool, FindLocalStatePref, (const std::string&), (const));
  MOCK_METHOD(std::optional<base::Value>,
              GetLocalStatePref,
              (const std::string&));
  MOCK_METHOD(void, SetLocalStatePref, (const std::string&, base::Value));
  MOCK_METHOD(void, ClearLocalStatePref, (const std::string&));
  MOCK_METHOD(bool, HasLocalStatePrefPath, (const std::string&), (const));

  MOCK_METHOD(base::DictValue, GetVirtualPrefs, (), (const));

  MOCK_METHOD(void, Log, (const char*, int, int, const std::string&));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_CLIENT_TEST_ADS_CLIENT_MOCK_H_
