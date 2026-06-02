/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_TOOLTIPS_ADS_TOOLTIPS_CONTROLLER_H_
#define CATSXP_BROWSER_CATSXP_ADS_TOOLTIPS_ADS_TOOLTIPS_CONTROLLER_H_

#include <string>

#include "catsxp/browser/ui/catsxp_tooltips/catsxp_tooltip_delegate.h"
#include "catsxp/components/catsxp_ads/browser/tooltips/ads_tooltips_delegate.h"

namespace catsxp_ads {

class AdsTooltipsController final
    : public AdsTooltipsDelegate,
      public catsxp_tooltips::CatsxpTooltipDelegate {
 public:
  AdsTooltipsController();

  AdsTooltipsController(const AdsTooltipsController&) = delete;
  AdsTooltipsController& operator=(const AdsTooltipsController&) = delete;

  ~AdsTooltipsController() override;

  // AdsTooltipDelegate:
  void ShowCaptchaTooltip(
      const std::string& payment_id,
      const std::string& captcha_id,
      bool include_cancel_button,
      ShowScheduledCaptchaCallback show_captcha_callback,
      SnoozeScheduledCaptchaCallback snooze_captcha_callback) override;
  void CloseCaptchaTooltip() override;

 private:
  // catsxp_tooltips::CatsxpTooltipDelegate:
  void OnTooltipWidgetDestroyed(const std::string& tooltip_id) override;

  base::WeakPtr<catsxp_tooltips::CatsxpTooltipDelegate> AsWeakPtr() override;

  base::WeakPtrFactory<CatsxpTooltipDelegate> weak_ptr_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_TOOLTIPS_ADS_TOOLTIPS_CONTROLLER_H_
