/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TOOLTIPS_ADS_TOOLTIPS_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TOOLTIPS_ADS_TOOLTIPS_DELEGATE_H_

#include <string>

#include "base/functional/callback.h"

namespace catsxp_ads {

using ShowScheduledCaptchaCallback =
    base::OnceCallback<void(const std::string& payment_id,
                            const std::string& captcha_id)>;
using SnoozeScheduledCaptchaCallback = base::OnceCallback<void()>;

class AdsTooltipsDelegate {
 public:
  virtual ~AdsTooltipsDelegate() = default;

  // Called to show the captcha tooltip.
  virtual void ShowCaptchaTooltip(
      const std::string& payment_id,
      const std::string& captcha_id,
      bool include_cancel_button,
      ShowScheduledCaptchaCallback show_captcha_callback,
      SnoozeScheduledCaptchaCallback snooze_captcha_callback) = 0;

  // Called to close the captcha tooltip.
  virtual void CloseCaptchaTooltip() = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TOOLTIPS_ADS_TOOLTIPS_DELEGATE_H_
