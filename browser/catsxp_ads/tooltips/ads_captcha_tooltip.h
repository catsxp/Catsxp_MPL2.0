/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_TOOLTIPS_ADS_CAPTCHA_TOOLTIP_H_
#define CATSXP_BROWSER_CATSXP_ADS_TOOLTIPS_ADS_CAPTCHA_TOOLTIP_H_

#include <string>

#include "catsxp/browser/ui/catsxp_tooltips/catsxp_tooltip.h"
#include "catsxp/browser/ui/catsxp_tooltips/catsxp_tooltip_attributes.h"
#include "catsxp/components/catsxp_ads/browser/tooltips/ads_tooltips_delegate.h"

namespace catsxp_ads {

inline constexpr char kScheduledCaptchaTooltipId[] = "scheduled-captcha";

class AdsCaptchaTooltip final : public catsxp_tooltips::CatsxpTooltip {
 public:
  AdsCaptchaTooltip(ShowScheduledCaptchaCallback show_captcha_callback,
                    SnoozeScheduledCaptchaCallback snooze_captcha_callback,
                    const catsxp_tooltips::CatsxpTooltipAttributes& attributes,
                    const std::string& payment_id,
                    const std::string& captcha_id);

  AdsCaptchaTooltip(const AdsCaptchaTooltip&) = delete;
  AdsCaptchaTooltip& operator=(const AdsCaptchaTooltip&) = delete;

  ~AdsCaptchaTooltip() override;

  const std::string& payment_id() const { return payment_id_; }
  const std::string& captcha_id() const { return captcha_id_; }

  // catsxp_tooltips::CatsxpTooltip:
  void PerformOkButtonAction() override;
  void PerformCancelButtonAction() override;

 private:
  ShowScheduledCaptchaCallback show_captcha_callback_;
  SnoozeScheduledCaptchaCallback snooze_captcha_callback_;
  std::string payment_id_;
  std::string captcha_id_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_TOOLTIPS_ADS_CAPTCHA_TOOLTIP_H_
