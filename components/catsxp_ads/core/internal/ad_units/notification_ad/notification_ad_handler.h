/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_HANDLER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_HANDLER_H_

#include <string>

#include "base/memory/raw_ref.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/notification_ad_serving.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/notification_ad_serving_delegate.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_handler.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_handler_delegate.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

class AdsClient;
class AntiTargetingResource;
class BrowserManager;
class SiteVisit;
class SubdivisionTargeting;
struct NotificationAdInfo;

class NotificationAdHandler final : public AdsClientNotifierObserver,
                                    public BrowserManagerObserver,
                                    public NotificationAdEventHandlerDelegate,
                                    public NotificationAdServingDelegate {
 public:
  NotificationAdHandler(SiteVisit& site_visit,
                        const SubdivisionTargeting& subdivision_targeting,
                        const AntiTargetingResource& anti_targeting_resource);

  NotificationAdHandler(const NotificationAdHandler&) = delete;
  NotificationAdHandler& operator=(const NotificationAdHandler&) = delete;

  ~NotificationAdHandler() override;

  void TriggerEvent(const std::string& placement_id,
                    mojom::NotificationAdEventType mojom_ad_event_type,
                    ResultCallback callback);

 private:
  void MaybeServeAtRegularIntervals();

  void FireServedEventCallback(
      ResultCallback callback,
      bool success,
      const std::string& placement_id,
      mojom::NotificationAdEventType mojom_ad_event_type);

  // AdsClientNotifierObserver:
  void OnNotifyDidInitializeAds() override;
  void OnNotifyPrefDidChange(const std::string& path) override;
  void OnNotifyUserDidBecomeActive(base::TimeDelta idle_time,
                                   bool screen_was_locked) override;

  // BrowserManagerObserver:
  void OnBrowserDidEnterForeground() override;
  void OnBrowserDidEnterBackground() override;

  // NotificationAdServingDelegate:
  void OnOpportunityAroseToServeNotificationAd(
      const SegmentList& segments) override;
  void OnDidServeNotificationAd(const NotificationAdInfo& ad) override;

  // NotificationAdEventHandlerDelegate:
  void OnWillFireNotificationAdClickedEvent(
      const NotificationAdInfo& ad) override;
  void OnDidFireNotificationAdServedEvent(
      const NotificationAdInfo& ad) override;
  void OnDidFireNotificationAdViewedEvent(
      const NotificationAdInfo& ad) override;
  void OnDidFireNotificationAdClickedEvent(
      const NotificationAdInfo& ad) override;
  void OnDidFireNotificationAdDismissedEvent(
      const NotificationAdInfo& ad) override;
  void OnDidFireNotificationAdTimedOutEvent(
      const NotificationAdInfo& ad) override;

  const raw_ref<SiteVisit> site_visit_;

  NotificationAdEventHandler event_handler_;

  NotificationAdServing serving_;

  base::ScopedObservation<AdsClient, AdsClientNotifierObserver>
      ads_client_observation_{this};

  base::ScopedObservation<BrowserManager, BrowserManagerObserver>
      browser_manager_observation_{this};

  base::WeakPtrFactory<NotificationAdHandler> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_HANDLER_H_
