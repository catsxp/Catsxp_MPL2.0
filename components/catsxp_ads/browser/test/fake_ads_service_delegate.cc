/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/test/fake_ads_service_delegate.h"

namespace catsxp_ads::test {

FakeAdsServiceDelegate::FakeAdsServiceDelegate() = default;

FakeAdsServiceDelegate::~FakeAdsServiceDelegate() = default;

void FakeAdsServiceDelegate::MaybeInitNotificationHelper() {}

bool FakeAdsServiceDelegate::
    CanShowSystemNotificationsWhileBrowserIsBackgrounded() {
  return false;
}

bool FakeAdsServiceDelegate::DoesSupportSystemNotifications() {
  return false;
}

bool FakeAdsServiceDelegate::CanShowNotifications() {
  return false;
}

bool FakeAdsServiceDelegate::ShowOnboardingNotification() {
  return false;
}

void FakeAdsServiceDelegate::ShowScheduledCaptcha(
    const std::string& /*payment_id*/,
    const std::string& /*captcha_id*/) {}

void FakeAdsServiceDelegate::ClearScheduledCaptcha() {}

void FakeAdsServiceDelegate::SnoozeScheduledCaptcha() {}

void FakeAdsServiceDelegate::ShowNotificationAd(
    const std::string& /*id*/,
    const std::u16string& /*title*/,
    const std::u16string& /*body*/) {}

void FakeAdsServiceDelegate::CloseNotificationAd(const std::string& /*id*/) {}

void FakeAdsServiceDelegate::OpenNewTabWithUrl(const GURL& /*url*/) {}

bool FakeAdsServiceDelegate::IsFullScreenMode() {
  return false;
}

std::string FakeAdsServiceDelegate::GetVariationsCountryCode() {
  return "US";
}

}  // namespace catsxp_ads::test
