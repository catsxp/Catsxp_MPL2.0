/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_NOTIFIER_MANAGER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_NOTIFIER_MANAGER_H_

#include <memory>
#include <vector>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

class AdsObserver;

class AdsNotifierManager final {
 public:
  AdsNotifierManager();

  AdsNotifierManager(const AdsNotifierManager& other) = delete;
  AdsNotifierManager& operator=(const AdsNotifierManager& other) = delete;

  ~AdsNotifierManager();

  static AdsNotifierManager& GetInstance();

  void AddObserver(std::unique_ptr<AdsObserver> ads_observer);

  void NotifyAdRewardsDidChange() const;

  void NotifyBrowserUpgradeRequiredToServeAds() const;

  void NotifyIneligibleWalletToServeAds() const;

  void NotifyRemindUser(mojom::ReminderType mojom_reminder_type) const;

 private:
  std::vector<std::unique_ptr<AdsObserver>> observers_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_NOTIFIER_MANAGER_H_
