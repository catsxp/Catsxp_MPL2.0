/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_OBSERVER_H_

#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

class AdsObserver {
 public:
  virtual ~AdsObserver() = default;

  // Invoked when ad rewards have changed.
  virtual void OnAdRewardsDidChange() = 0;

  // Invoked when a browser upgrade is required to serve ads.
  virtual void OnBrowserUpgradeRequiredToServeAds() = 0;

  // Invoked when a wallet is deemed ineligible to serve ads.
  virtual void OnIneligibleWalletToServeAds() = 0;

  // Invoked to remind the user of what to do and what not to do.
  virtual void OnRemindUser(mojom::ReminderType mojom_reminder_type) = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_ADS_OBSERVER_H_
