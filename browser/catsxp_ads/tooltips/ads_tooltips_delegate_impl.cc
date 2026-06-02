/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/tooltips/ads_tooltips_delegate_impl.h"

#include <utility>

namespace catsxp_ads {

AdsTooltipsDelegateImpl::AdsTooltipsDelegateImpl() {}

void AdsTooltipsDelegateImpl::ShowCaptchaTooltip(
    const std::string& payment_id,
    const std::string& captcha_id,
    bool include_cancel_button,
    ShowScheduledCaptchaCallback show_captcha_callback,
    SnoozeScheduledCaptchaCallback snooze_captcha_callback) {
  ads_tooltips_controller_.ShowCaptchaTooltip(
      payment_id, captcha_id, include_cancel_button,
      std::move(show_captcha_callback), std::move(snooze_captcha_callback));
}

void AdsTooltipsDelegateImpl::CloseCaptchaTooltip() {
  ads_tooltips_controller_.CloseCaptchaTooltip();
}

}  // namespace catsxp_ads
