/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_ADS_ADS_SERVICE_DELEGATE_H_
#define CATSXP_BROWSER_CATSXP_ADS_ADS_SERVICE_DELEGATE_H_

#include <string>

#include "base/memory/raw_ptr.h"
#include "base/memory/raw_ref.h"
#include "catsxp/components/catsxp_ads/core/browser/service/ads_service.h"
#include "catsxp/components/catsxp_rewards/core/buildflags/buildflags.h"

class GURL;
class NotificationDisplayService;
class PrefService;
class Profile;

#if BUILDFLAG(ENABLE_CATSXP_REWARDS)
namespace catsxp_adaptive_captcha {
class CatsxpAdaptiveCaptchaService;
}  // namespace catsxp_adaptive_captcha
#endif

class NotificationDisplayService;

namespace catsxp_ads {

// Browser-layer, platform-specific implementation of AdsService::Delegate.
class AdsServiceDelegate final : public AdsService::Delegate {
 public:
  // `adaptive_captcha_service` can be `nullptr` in tests.
  AdsServiceDelegate(Profile& profile,
                     PrefService& local_state
#if BUILDFLAG(ENABLE_CATSXP_REWARDS)
                     ,
                     catsxp_adaptive_captcha::CatsxpAdaptiveCaptchaService*
                         adaptive_captcha_service
#endif
  );

  AdsServiceDelegate(const AdsServiceDelegate&) = delete;
  AdsServiceDelegate& operator=(const AdsServiceDelegate&) = delete;

  ~AdsServiceDelegate() override;

  // AdsService::Delegate:
  void MaybeInitNotificationHelper() override;
  bool CanShowSystemNotificationsWhileBrowserIsBackgrounded() override;
  bool DoesSupportSystemNotifications() override;
  bool CanShowNotifications() override;
  bool ShowOnboardingNotification() override;
#if BUILDFLAG(ENABLE_CATSXP_REWARDS)
  void ShowScheduledCaptcha(const std::string& payment_id,
                            const std::string& captcha_id) override;
  void ClearScheduledCaptcha() override;
  void SnoozeScheduledCaptcha() override;
#endif
  void ShowNotificationAd(const std::string& id,
                          const std::u16string& title,
                          const std::u16string& body) override;
  void CloseNotificationAd(const std::string& id) override;
  void OpenNewTabWithUrl(const GURL& url) override;
  bool IsFullScreenMode() override;
  std::string GetVariationsCountryCode() override;

 private:
  NotificationDisplayService* GetNotificationDisplayService();

  const raw_ref<Profile> profile_;
  const raw_ref<PrefService> local_state_; // Not owned.
#if BUILDFLAG(ENABLE_CATSXP_REWARDS)
  const raw_ptr<catsxp_adaptive_captcha::CatsxpAdaptiveCaptchaService>
      adaptive_captcha_service_;  // Not owned.
#endif
};

}  // namespace catsxp_ads

#endif  // CATSXP_BROWSER_CATSXP_ADS_ADS_SERVICE_DELEGATE_H_
