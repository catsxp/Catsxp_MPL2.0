/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/test/fake_ads_tooltips_delegate.h"

namespace catsxp_ads::test {

FakeAdsTooltipsDelegate::FakeAdsTooltipsDelegate() = default;

FakeAdsTooltipsDelegate::~FakeAdsTooltipsDelegate() = default;

void FakeAdsTooltipsDelegate::ShowCaptchaTooltip(
    const std::string& /*payment_id*/,
    const std::string& /*captcha_id*/,
    bool /*include_cancel_button*/,
    ShowScheduledCaptchaCallback /*show_captcha_callback*/,
    SnoozeScheduledCaptchaCallback /*snooze_captcha_callback*/) {}

void FakeAdsTooltipsDelegate::CloseCaptchaTooltip() {}

}  // namespace catsxp_ads::test
