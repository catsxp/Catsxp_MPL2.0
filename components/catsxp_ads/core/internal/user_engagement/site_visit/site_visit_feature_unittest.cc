/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/site_visit/site_visit_feature.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsSiteVisitFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kSiteVisitFeature));
}

TEST(CatsxpAdsSiteVisitFeatureTest, PageLandAfter) {
  // Act & Assert
  EXPECT_EQ(base::Seconds(5), kPageLandAfter.Get());
}

TEST(CatsxpAdsSiteVisitFeatureTest, PageLandCap) {
  // Act & Assert
  EXPECT_EQ(0U, kPageLandCap.Get());
}

TEST(CatsxpAdsSiteVisitFeatureTest, ShouldSuspendAndResumePageLand) {
  // Act & Assert
  EXPECT_TRUE(kShouldSuspendAndResumePageLand.Get());
}

}  // namespace catsxp_ads
