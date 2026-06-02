/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/reminders/reminders_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsRemindersFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kRemindersFeature));
}

TEST(CatsxpAdsRemindersFeatureTest, RemindUserIfClickingTheSameAdAfter) {
  // Act & Assert
  EXPECT_EQ(3U, kRemindUserIfClickingTheSameAdAfter.Get());
}

}  // namespace catsxp_ads
