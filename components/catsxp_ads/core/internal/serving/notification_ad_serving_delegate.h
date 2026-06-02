/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NOTIFICATION_AD_SERVING_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NOTIFICATION_AD_SERVING_DELEGATE_H_

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

namespace catsxp_ads {

struct NotificationAdInfo;

class NotificationAdServingDelegate {
 public:
  // Invoked when an opportunity arises to serve a notification ad.
  virtual void OnOpportunityAroseToServeNotificationAd(
      const SegmentList& segments) {}

  // Invoked when a notification ad is served.
  virtual void OnDidServeNotificationAd(const NotificationAdInfo& ad) {}

  // Invoked when a notification ad fails to serve.
  virtual void OnFailedToServeNotificationAd() {}

 protected:
  virtual ~NotificationAdServingDelegate() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NOTIFICATION_AD_SERVING_DELEGATE_H_
