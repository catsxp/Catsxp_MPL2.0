/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_MANAGER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_MANAGER_H_

#include <cstdint>

#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/internal/tabs/tab_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_event_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_event_types.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_notifier_observer.h"
#include "ui/base/page_transition_types.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

class AdsClient;
class BrowserManager;
class TabManager;
struct TabInfo;

class UserActivityManager final : public AdsClientNotifierObserver,
                                  public BrowserManagerObserver,
                                  public TabManagerObserver {
 public:
  UserActivityManager();

  UserActivityManager(const UserActivityManager&) = delete;
  UserActivityManager& operator=(const UserActivityManager&) = delete;

  ~UserActivityManager() override;

  static UserActivityManager& GetInstance();

  void RecordEvent(UserActivityEventType event_type);

  UserActivityEventList GetHistoryForTimeWindow(
      base::TimeDelta time_window) const;

 private:
  void RecordEventForPageTransition(ui::PageTransition page_transition);

  // AdsClientNotifierObserver:
  void OnNotifyDidInitializeAds() override;
  void OnNotifyUserGestureEventTriggered(
      ui::PageTransition page_transition) override;

  // BrowserManagerObserver:
  void OnBrowserDidBecomeActive() override;
  void OnBrowserDidResignActive() override;
  void OnBrowserDidEnterForeground() override;
  void OnBrowserDidEnterBackground() override;

  // TabManagerObserver:
  void OnDidOpenNewTab(const TabInfo& tab) override;
  void OnTabDidChangeFocus(int32_t tab_id) override;
  void OnTabDidChange(const TabInfo& tab) override;
  void OnDidCloseTab(int32_t tab_id) override;
  void OnTabDidStartPlayingMedia(int32_t tab_id) override;
  void OnTabDidStopPlayingMedia(int32_t tab_id) override;

  UserActivityEventList user_activity_events_;

  base::ScopedObservation<AdsClient, AdsClientNotifierObserver>
      ads_client_observation_{this};

  base::ScopedObservation<BrowserManager, BrowserManagerObserver>
      browser_manager_observation_{this};

  base::ScopedObservation<TabManager, TabManagerObserver>
      tab_manager_observation_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_MANAGER_H_
