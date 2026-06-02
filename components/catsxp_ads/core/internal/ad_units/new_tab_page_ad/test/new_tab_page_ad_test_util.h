/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NEW_TAB_PAGE_AD_TEST_NEW_TAB_PAGE_AD_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NEW_TAB_PAGE_AD_TEST_NEW_TAB_PAGE_AD_TEST_UTIL_H_

#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"

namespace catsxp_ads {

struct NewTabPageAdInfo;

namespace test {

NewTabPageAdInfo BuildNewTabPageAd(
    CreativeNewTabPageAdWallpaperType wallpaper_type,
    bool use_random_uuids);

NewTabPageAdInfo BuildAndSaveNewTabPageAd(
    CreativeNewTabPageAdWallpaperType wallpaper_type,
    bool use_random_uuids);

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_NEW_TAB_PAGE_AD_TEST_NEW_TAB_PAGE_AD_TEST_UTIL_H_
