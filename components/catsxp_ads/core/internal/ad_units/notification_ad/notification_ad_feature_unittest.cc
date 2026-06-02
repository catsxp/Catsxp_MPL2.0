/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_feature.h"

#include "base/time/time.h"
#include "build/build_config.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsNotificationAdFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kNotificationAdFeature));
}

TEST(CatsxpAdsNotificationAdFeatureTest, NotificationAdTimeout) {
  // Act & Assert
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)
  EXPECT_EQ(base::Minutes(2), kNotificationAdTimeout.Get());
#else
  EXPECT_EQ(base::Seconds(30), kNotificationAdTimeout.Get());
#endif  // !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)
}

TEST(CatsxpAdsNotificationAdFeatureTest, DefaultNotificationAdsPerHour) {
  // Act & Assert
  EXPECT_EQ(10, kDefaultNotificationAdsPerHour.Get());
}

TEST(CatsxpAdsNotificationAdFeatureTest, MaximumNotificationAdsPerDay) {
  // Act & Assert
  EXPECT_EQ(100U, kMaximumNotificationAdsPerDay.Get());
}

}  // namespace catsxp_ads
