/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_ADS_TOOLTIPS_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_ADS_TOOLTIPS_DELEGATE_H_

#include <string>

#include "catsxp/components/catsxp_ads/browser/tooltips/ads_tooltips_delegate.h"

namespace catsxp_ads::test {

// No-op implementation of `AdsTooltipsDelegate` for unit tests.
class FakeAdsTooltipsDelegate : public AdsTooltipsDelegate {
 public:
  FakeAdsTooltipsDelegate();

  FakeAdsTooltipsDelegate(const FakeAdsTooltipsDelegate&) = delete;
  FakeAdsTooltipsDelegate& operator=(const FakeAdsTooltipsDelegate&) = delete;

  ~FakeAdsTooltipsDelegate() override;

  // AdsTooltipsDelegate:
  void ShowCaptchaTooltip(
      const std::string& payment_id,
      const std::string& captcha_id,
      bool include_cancel_button,
      ShowScheduledCaptchaCallback show_captcha_callback,
      SnoozeScheduledCaptchaCallback snooze_captcha_callback) override;
  void CloseCaptchaTooltip() override;
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_ADS_TOOLTIPS_DELEGATE_H_
