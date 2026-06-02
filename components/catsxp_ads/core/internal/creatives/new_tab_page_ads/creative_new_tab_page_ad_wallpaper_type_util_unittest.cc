/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type_util.h"

#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCreativeNewTabPageAdWallpaperTypeUtilTest,
     StringToCreativeNewTabPageAdImageWallpaperType) {
  // Act & Assert
  EXPECT_EQ(CreativeNewTabPageAdWallpaperType::kImage,
            ToCreativeNewTabPageAdWallpaperType("image"));
}

TEST(CatsxpAdsCreativeNewTabPageAdWallpaperTypeUtilTest,
     StringToCreativeNewTabPageAdWallpaperType) {
  // Act & Assert
  EXPECT_EQ(CreativeNewTabPageAdWallpaperType::kRichMedia,
            ToCreativeNewTabPageAdWallpaperType("richMedia"));
}

TEST(CatsxpAdsCreativeNewTabPageAdWallpaperTypeUtilTest,
     CreativeNewTabPageAdImageWallpaperTypeToString) {
  // Act & Assert
  EXPECT_EQ("image", ToString(CreativeNewTabPageAdWallpaperType::kImage));
}

TEST(CatsxpAdsCreativeNewTabPageAdWallpaperTypeUtilTest,
     CreativeNewTabPageAdRichMediaWallpaperTypeToString) {
  // Act & Assert
  EXPECT_EQ("richMedia",
            ToString(CreativeNewTabPageAdWallpaperType::kRichMedia));
}

}  // namespace catsxp_ads
