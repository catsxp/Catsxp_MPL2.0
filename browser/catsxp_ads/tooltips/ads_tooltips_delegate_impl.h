/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_TOOLTIPS_ADS_TOOLTIPS_DELEGATE_IMPL_H_
#define CATSXP_BROWSER_CATSXP_ADS_TOOLTIPS_ADS_TOOLTIPS_DELEGATE_IMPL_H_

#include <string>

#include "catsxp/browser/catsxp_ads/tooltips/ads_tooltips_controller.h"
#include "catsxp/components/catsxp_ads/browser/tooltips/ads_tooltips_delegate.h"

namespace catsxp_ads {

class AdsTooltipsDelegateImpl final : public AdsTooltipsDelegate {
 public:
  AdsTooltipsDelegateImpl();

  AdsTooltipsDelegateImpl(const AdsTooltipsDelegateImpl&) = delete;
  AdsTooltipsDelegateImpl& operator=(const AdsTooltipsDelegateImpl&) = delete;

  ~AdsTooltipsDelegateImpl() override = default;

  // AdsTooltipsDelegate:
  void ShowCaptchaTooltip(
      const std::string& payment_id,
      const std::string& captcha_id,
      bool include_cancel_button,
      ShowScheduledCaptchaCallback show_captcha_callback,
      SnoozeScheduledCaptchaCallback snooze_captcha_callback) override;
  void CloseCaptchaTooltip() override;

 private:
  AdsTooltipsController ads_tooltips_controller_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_TOOLTIPS_ADS_TOOLTIPS_DELEGATE_IMPL_H_
