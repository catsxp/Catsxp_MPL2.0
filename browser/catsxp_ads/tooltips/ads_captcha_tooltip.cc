/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/tooltips/ads_captcha_tooltip.h"

#include <utility>

namespace catsxp_ads {

AdsCaptchaTooltip::AdsCaptchaTooltip(
    ShowScheduledCaptchaCallback show_captcha_callback,
    SnoozeScheduledCaptchaCallback snooze_captcha_callback,
    const catsxp_tooltips::CatsxpTooltipAttributes& attributes,
    const std::string& payment_id,
    const std::string& captcha_id)
    : CatsxpTooltip(kScheduledCaptchaTooltipId, attributes, nullptr),
      show_captcha_callback_(std::move(show_captcha_callback)),
      snooze_captcha_callback_(std::move(snooze_captcha_callback)),
      payment_id_(payment_id),
      captcha_id_(captcha_id) {}

AdsCaptchaTooltip::~AdsCaptchaTooltip() = default;

void AdsCaptchaTooltip::PerformOkButtonAction() {
  // User chose to solve the captcha now, so show it to initiate that process
  if (show_captcha_callback_) {
    std::move(show_captcha_callback_).Run(payment_id_, captcha_id_);
  }
}

void AdsCaptchaTooltip::PerformCancelButtonAction() {
  // In this context, cancel means snooze the captcha for now
  if (snooze_captcha_callback_) {
    std::move(snooze_captcha_callback_).Run();
  }
}

}  // namespace catsxp_ads
