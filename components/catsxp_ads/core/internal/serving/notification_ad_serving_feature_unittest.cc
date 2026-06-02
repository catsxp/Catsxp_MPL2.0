/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/notification_ad_serving_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsNotificationAdServingFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kNotificationAdServingFeature));
}

TEST(CatsxpAdsNotificationAdServingFeatureTest, NotificationAdServingVersion) {
  // Act & Assert
  EXPECT_EQ(2, kNotificationAdServingVersion.Get());
}

TEST(CatsxpAdsNotificationAdServingFeatureTest, ServeFirstNotificationAdAfter) {
  // Act & Assert
  EXPECT_EQ(base::Minutes(2), kServeFirstNotificationAdAfter.Get());
}

TEST(CatsxpAdsNotificationAdServingFeatureTest,
     MinimumDelayBeforeServingNotificationAd) {
  // Act & Assert
  EXPECT_EQ(base::Minutes(1), kMinimumDelayBeforeServingNotificationAd.Get());
}

TEST(CatsxpAdsNotificationAdServingFeatureTest,
     RetryServingNotificationAdAfter) {
  // Act & Assert
  EXPECT_EQ(base::Minutes(2), kRetryServingNotificationAdAfter.Get());
}

}  // namespace catsxp_ads
