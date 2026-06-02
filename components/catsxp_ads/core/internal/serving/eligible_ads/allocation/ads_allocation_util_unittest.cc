/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/allocation/ads_allocation_util.h"

#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/test/creative_new_tab_page_ad_test_util.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCreativeAdAllocationUtilTest,
     RandomlyChosenAdIsAlwaysFromTheEligibleList) {
  // Arrange
  const CreativeNewTabPageAdList creative_ads =
      test::BuildCreativeNewTabPageAds(
          CreativeNewTabPageAdWallpaperType::kImage, /*count=*/3);

  // Act
  const CreativeNewTabPageAdInfo chosen_creative_ad =
      ChooseCreativeAdAtRandom(creative_ads);

  // Assert
  EXPECT_THAT(creative_ads, testing::Contains(chosen_creative_ad));
}

TEST(CatsxpAdsCreativeAdAllocationUtilTest,
     SingleEligibleAdIsAlwaysTheRandomChoice) {
  // Arrange
  const CreativeNewTabPageAdList creative_ads =
      test::BuildCreativeNewTabPageAds(
          CreativeNewTabPageAdWallpaperType::kImage, /*count=*/1);

  // Act
  const CreativeNewTabPageAdInfo chosen_creative_ad =
      ChooseCreativeAdAtRandom(creative_ads);

  // Assert
  EXPECT_EQ(chosen_creative_ad.creative_instance_id,
            creative_ads.front().creative_instance_id);
}

}  // namespace catsxp_ads
