/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_TEST_CREATIVE_NEW_TAB_PAGE_AD_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_TEST_CREATIVE_NEW_TAB_PAGE_AD_TEST_UTIL_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"

namespace catsxp_ads::test {

CreativeNewTabPageAdList BuildCreativeNewTabPageAds(
    CreativeNewTabPageAdWallpaperType wallpaper_type,
    size_t count);
CreativeNewTabPageAdInfo BuildCreativeNewTabPageAd(
    CreativeNewTabPageAdWallpaperType wallpaper_type,
    bool use_random_uuids);

void SaveCreativeNewTabPageAds(const CreativeNewTabPageAdList& creative_ads);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_TEST_CREATIVE_NEW_TAB_PAGE_AD_TEST_UTIL_H_
