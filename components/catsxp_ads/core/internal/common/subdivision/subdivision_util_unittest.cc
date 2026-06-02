/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/subdivision_util.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsSubdivisionUtilTest, GetSubdivisionCountryCode) {
  // Act & Assert
  EXPECT_EQ("US", GetSubdivisionCountryCode(/*subdivision=*/"US-CA"));
}

TEST(CatsxpAdsSubdivisionUtilTest, DoNotGetSubdivisionCountryCode) {
  // Act & Assert
  EXPECT_FALSE(GetSubdivisionCountryCode(/*subdivision=*/""));
}

TEST(CatsxpAdsSubdivisionUtilTest, GetSubdivisionCode) {
  // Act & Assert
  EXPECT_EQ("CA", GetSubdivisionCode(/*subdivision=*/"US-CA"));
}

TEST(CatsxpAdsSubdivisionUtilTest, DoNotGetSubdivisionCode) {
  // Act & Assert
  EXPECT_FALSE(GetSubdivisionCode(/*subdivision=*/""));
}

}  // namespace catsxp_ads
