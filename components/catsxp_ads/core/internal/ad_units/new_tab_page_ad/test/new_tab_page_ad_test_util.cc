/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ad_units/new_tab_page_ad/test/new_tab_page_ad_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/new_tab_page_ad_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/test/creative_new_tab_page_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"

namespace catsxp_ads::test {

NewTabPageAdInfo BuildNewTabPageAd(
    CreativeNewTabPageAdWallpaperType wallpaper_type,
    bool use_random_uuids) {
  const CreativeNewTabPageAdInfo creative_ad =
      BuildCreativeNewTabPageAd(wallpaper_type, use_random_uuids);
  return BuildNewTabPageAd(creative_ad);
}

NewTabPageAdInfo BuildAndSaveNewTabPageAd(
    CreativeNewTabPageAdWallpaperType wallpaper_type,
    bool use_random_uuids) {
  const CreativeNewTabPageAdInfo creative_ad =
      BuildCreativeNewTabPageAd(wallpaper_type, use_random_uuids);
  SaveCreativeNewTabPageAds({creative_ad});
  return BuildNewTabPageAd(creative_ad);
}

}  // namespace catsxp_ads::test
