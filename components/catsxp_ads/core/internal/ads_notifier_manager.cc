/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ads_notifier_manager.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ads_observer.h"

namespace catsxp_ads {

AdsNotifierManager::AdsNotifierManager() = default;

AdsNotifierManager::~AdsNotifierManager() = default;

// static
AdsNotifierManager& AdsNotifierManager::GetInstance() {
  return GlobalState::GetInstance()->GetAdsNotifierManager();
}

void AdsNotifierManager::AddObserver(std::unique_ptr<AdsObserver> observer) {
  observers_.push_back(std::move(observer));
}

void AdsNotifierManager::NotifyAdRewardsDidChange() const {
  for (const auto& ads_observer : observers_) {
    ads_observer->OnAdRewardsDidChange();
  }
}

void AdsNotifierManager::NotifyBrowserUpgradeRequiredToServeAds() const {
  for (const auto& ads_observer : observers_) {
    ads_observer->OnBrowserUpgradeRequiredToServeAds();
  }
}

void AdsNotifierManager::NotifyIneligibleWalletToServeAds() const {
  for (const auto& ads_observer : observers_) {
    ads_observer->OnIneligibleWalletToServeAds();
  }
}

void AdsNotifierManager::NotifyRemindUser(
    mojom::ReminderType mojom_reminder_type) const {
  for (const auto& ads_observer : observers_) {
    ads_observer->OnRemindUser(mojom_reminder_type);
  }
}

}  // namespace catsxp_ads
