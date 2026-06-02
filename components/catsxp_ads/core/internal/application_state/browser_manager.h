/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_MANAGER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_MANAGER_H_

#include <optional>

#include "base/observer_list.h"
#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace catsxp_ads {

class AdsClient;

class BrowserManager final : public AdsClientNotifierObserver {
 public:
  BrowserManager();

  BrowserManager(const BrowserManager&) = delete;
  BrowserManager& operator=(const BrowserManager&) = delete;

  ~BrowserManager() override;

  static BrowserManager& GetInstance();

  void AddObserver(BrowserManagerObserver* observer);
  void RemoveObserver(BrowserManagerObserver* observer);

  bool IsActive() const { return is_active_.value_or(false); }

  bool IsInForeground() const { return is_in_foreground_.value_or(false); }

 private:
  bool IsCurrentlyActive() const;
  void NotifyBrowserDidBecomeActive();
  bool IsCurrentlyInactive() const;
  void NotifyBrowserDidResignActive();
  void LogBrowserActiveState() const;

  bool IsCurrentlyInForeground() const;
  void NotifyBrowserDidEnterForeground();
  bool IsCurrentlyInBackground() const;
  void NotifyBrowserDidEnterBackground();
  void InitializeBrowserBackgroundState();
  void LogBrowserBackgroundState() const;

  // AdsClientNotifierObserver:
  void OnNotifyDidInitializeAds() override;
  void OnNotifyBrowserDidBecomeActive() override;
  void OnNotifyBrowserDidResignActive() override;
  void OnNotifyBrowserDidEnterForeground() override;
  void OnNotifyBrowserDidEnterBackground() override;

  base::ObserverList<BrowserManagerObserver> observers_;

  base::ScopedObservation<AdsClient, AdsClientNotifierObserver>
      ads_client_observation_{this};

  std::optional<bool> is_active_;

  std::optional<bool> is_in_foreground_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_MANAGER_H_
