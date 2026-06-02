/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/strings/string_conversions_util.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsStringConversionsUtilTest, TrueBoolToString) {
  // Act & Assert
  EXPECT_EQ("true", BoolToString(true));
}

TEST(CatsxpAdsStringConversionsUtilTest, FalseBoolToString) {
  // Act & Assert
  EXPECT_EQ("false", BoolToString(false));
}

}  // namespace catsxp_ads
