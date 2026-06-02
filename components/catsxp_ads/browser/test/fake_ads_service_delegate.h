/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_ADS_SERVICE_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_ADS_SERVICE_DELEGATE_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/browser/service/ads_service.h"

class GURL;

namespace catsxp_ads::test {

// Minimal no-op implementation of `AdsService::Delegate` for use in unit
// tests that exercise `AdsServiceImpl` without a real browser environment.
class FakeAdsServiceDelegate : public AdsService::Delegate {
 public:
  FakeAdsServiceDelegate();

  FakeAdsServiceDelegate(const FakeAdsServiceDelegate&) = delete;
  FakeAdsServiceDelegate& operator=(const FakeAdsServiceDelegate&) = delete;

  ~FakeAdsServiceDelegate() override;

  // AdsService::Delegate:
  void MaybeInitNotificationHelper() override;
  bool CanShowSystemNotificationsWhileBrowserIsBackgrounded() override;
  bool DoesSupportSystemNotifications() override;
  bool CanShowNotifications() override;
  bool ShowOnboardingNotification() override;
  void ShowScheduledCaptcha(const std::string& payment_id,
                            const std::string& captcha_id) override;
  void ClearScheduledCaptcha() override;
  void SnoozeScheduledCaptcha() override;
  void ShowNotificationAd(const std::string& id,
                          const std::u16string& title,
                          const std::u16string& body) override;
  void CloseNotificationAd(const std::string& id) override;
  void OpenNewTabWithUrl(const GURL& url) override;
  bool IsFullScreenMode() override;
  std::string GetVariationsCountryCode() override;
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_ADS_SERVICE_DELEGATE_H_
