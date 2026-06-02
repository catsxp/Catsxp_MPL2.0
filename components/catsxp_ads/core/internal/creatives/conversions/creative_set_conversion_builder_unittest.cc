/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_builder.h"

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/search_result_ads/test/creative_search_result_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCreativeSetConversionBuilderTest : public test::TestBase {};

TEST_F(CatsxpAdsCreativeSetConversionBuilderTest,
       FromMojomMaybeBuildCreativeSetConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/false);

  // Act
  std::optional<CreativeSetConversionInfo> creative_set_conversion =
      FromMojomMaybeBuildCreativeSetConversion(mojom_creative_ad);
  ASSERT_TRUE(creative_set_conversion);

  // Assert
  EXPECT_THAT(
      *creative_set_conversion,
      ::testing::FieldsAre(test::kCreativeSetId,
                           /*url_pattern*/ "https://catsxp.com/*",
                           /*observation_window*/ base::Days(3),
                           /*expire_at*/ test::Now() + base::Days(3)));
}

TEST_F(CatsxpAdsCreativeSetConversionBuilderTest,
       DoNotBuildCreativeSetConversionIfUrlPatternIsAbsent) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/false);
  mojom_creative_ad->creative_set_conversion->url_pattern.reset();

  // Act & Assert
  EXPECT_FALSE(FromMojomMaybeBuildCreativeSetConversion(mojom_creative_ad));
}

TEST_F(CatsxpAdsCreativeSetConversionBuilderTest,
       DoNotBuildCreativeSetConversionIfAdDoesNotSupportConversions) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAd(/*use_random_uuids=*/false);

  // Act & Assert
  EXPECT_FALSE(FromMojomMaybeBuildCreativeSetConversion(mojom_creative_ad));
}

}  // namespace catsxp_ads
