/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TEST_NOTIFICATION_AD_SERVING_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TEST_NOTIFICATION_AD_SERVING_DELEGATE_MOCK_H_

#include "catsxp/components/catsxp_ads/core/internal/serving/notification_ad_serving_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class NotificationAdServingDelegateMock : public NotificationAdServingDelegate {
 public:
  NotificationAdServingDelegateMock();

  NotificationAdServingDelegateMock(const NotificationAdServingDelegateMock&) =
      delete;
  NotificationAdServingDelegateMock& operator=(
      const NotificationAdServingDelegateMock&) = delete;

  ~NotificationAdServingDelegateMock() override;

  MOCK_METHOD(void,
              OnOpportunityAroseToServeNotificationAd,
              (const SegmentList&));

  MOCK_METHOD(void, OnDidServeNotificationAd, (const NotificationAdInfo&));
  MOCK_METHOD(void, OnFailedToServeNotificationAd, ());
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TEST_NOTIFICATION_AD_SERVING_DELEGATE_MOCK_H_
