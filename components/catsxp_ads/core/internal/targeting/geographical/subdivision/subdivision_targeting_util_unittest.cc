/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/geographical/subdivision/subdivision_targeting_util.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsSubdivisionTargetingUtilTest, ShouldTargetSubdivisionCountryCode) {
  // Act & Assert
  EXPECT_TRUE(ShouldTargetSubdivisionCountryCode(
      /*United States of America*/ "US"));
  EXPECT_TRUE(ShouldTargetSubdivisionCountryCode(/*Canada*/ "CA"));
}

TEST(CatsxpAdsSubdivisionTargetingUtilTest,
     ShouldNotTargetSubdivisionCountryCode) {
  // Act & Assert
  EXPECT_FALSE(ShouldTargetSubdivisionCountryCode("XX"));
}

TEST(CatsxpAdsSubdivisionTargetingUtilTest, ShouldTargetSubdivision) {
  // Act & Assert
  EXPECT_TRUE(ShouldTargetSubdivision(
      /*United States of America*/ "US", /*subdivision=*/"US-CA"));
}

TEST(CatsxpAdsSubdivisionTargetingUtilTest, ShouldNotTargetSubdivision) {
  // Act & Assert
  EXPECT_FALSE(ShouldTargetSubdivision(
      /*United States of America*/ "US", /*subdivision=*/"US-XX"));
}

}  // namespace catsxp_ads
