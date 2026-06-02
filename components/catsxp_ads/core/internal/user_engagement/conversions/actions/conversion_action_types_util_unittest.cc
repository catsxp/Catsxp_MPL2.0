/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/actions/conversion_action_types_util.h"

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsConversionActionTypesUtilTest, ToViewThroughConversionActionType) {
  // Act & Assert
  EXPECT_EQ(ConversionActionType::kViewThrough,
            ToConversionActionType(mojom::ConfirmationType::kViewedImpression));
}

TEST(CatsxpAdsConversionActionTypesUtilTest,
     ToClickThroughConversionActionType) {
  // Act & Assert
  EXPECT_EQ(ConversionActionType::kClickThrough,
            ToConversionActionType(mojom::ConfirmationType::kClicked));
}

TEST(CatsxpAdsConversionActionTypesUtilTest,
     StringToViewThroughConversionActionType) {
  // Act & Assert
  EXPECT_EQ(ConversionActionType::kViewThrough, ToConversionActionType("view"));
}

TEST(CatsxpAdsConversionActionTypesUtilTest,
     StringToClickThroughConversionActionType) {
  // Act & Assert
  EXPECT_EQ(ConversionActionType::kClickThrough,
            ToConversionActionType("click"));
}

TEST(CatsxpAdsConversionActionTypesUtilTest,
     ViewThroughConversionActionTypeToString) {
  // Act & Assert
  EXPECT_EQ("view", ToString(ConversionActionType::kViewThrough));
}

TEST(CatsxpAdsConversionActionTypesUtilTest,
     ClickThroughConversionActionTypeToString) {
  // Act & Assert
  EXPECT_EQ("click", ToString(ConversionActionType::kClickThrough));
}

}  // namespace catsxp_ads
