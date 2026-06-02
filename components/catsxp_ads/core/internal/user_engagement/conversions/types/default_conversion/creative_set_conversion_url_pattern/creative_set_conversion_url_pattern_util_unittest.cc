/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/types/default_conversion/creative_set_conversion_url_pattern/creative_set_conversion_url_pattern_util.h"

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/test/creative_set_conversion_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/test/conversions_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/test/conversions_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCreativeConversionSetUrlPatternUtilTest : public test::TestBase {
};

TEST_F(CatsxpAdsCreativeConversionSetUrlPatternUtilTest,
       DoesCreativeSetConversionUrlPatternMatchRedirectChain) {
  // Arrange
  const CreativeSetConversionInfo creative_set_conversion =
      test::BuildCreativeSetConversion(test::kCreativeSetId,
                                       test::kMatchingUrlPattern,
                                       /*observation_window=*/base::Days(3));

  // Act & Assert
  EXPECT_TRUE(DoesCreativeSetConversionUrlPatternMatchRedirectChain(
      creative_set_conversion, test::BuildDefaultConversionRedirectChain()));
}

TEST_F(CatsxpAdsCreativeConversionSetUrlPatternUtilTest,
       DoesEmptyCreativeSetConversionUrlPatternNotMatchRedirectChain) {
  // Arrange
  const CreativeSetConversionInfo creative_set_conversion =
      test::BuildCreativeSetConversion(test::kCreativeSetId,
                                       /*url_pattern=*/"",
                                       /*observation_window=*/base::Days(3));

  // Act & Assert
  EXPECT_FALSE(DoesCreativeSetConversionUrlPatternMatchRedirectChain(
      creative_set_conversion, test::BuildDefaultConversionRedirectChain()));
}

TEST_F(CatsxpAdsCreativeConversionSetUrlPatternUtilTest,
       DoesCreativeSetConversionUrlPatternNotMatchRedirectChain) {
  // Arrange
  const CreativeSetConversionInfo creative_set_conversion =
      test::BuildCreativeSetConversion(test::kCreativeSetId,
                                       test::kMismatchingUrlPattern,
                                       /*observation_window=*/base::Days(3));

  // Act & Assert
  EXPECT_FALSE(DoesCreativeSetConversionUrlPatternMatchRedirectChain(
      creative_set_conversion, test::BuildDefaultConversionRedirectChain()));
}

}  // namespace catsxp_ads
