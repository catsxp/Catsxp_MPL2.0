/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_AD_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_AD_INFO_H_

#include <string>
#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"

namespace catsxp_ads {

struct CreativeNewTabPageAdInfo final : CreativeAdInfo {
  CreativeNewTabPageAdInfo();
  explicit CreativeNewTabPageAdInfo(const CreativeAdInfo& creative_ad);

  CreativeNewTabPageAdInfo(const CreativeNewTabPageAdInfo&);
  CreativeNewTabPageAdInfo& operator=(const CreativeNewTabPageAdInfo&);

  CreativeNewTabPageAdInfo(CreativeNewTabPageAdInfo&&) noexcept;
  CreativeNewTabPageAdInfo& operator=(CreativeNewTabPageAdInfo&&) noexcept;

  ~CreativeNewTabPageAdInfo();

  bool operator==(const CreativeNewTabPageAdInfo&) const = default;

  CreativeNewTabPageAdWallpaperType wallpaper_type =
      CreativeNewTabPageAdWallpaperType::kUndefined;
  std::string company_name;
  std::string alt;
};

using CreativeNewTabPageAdList = std::vector<CreativeNewTabPageAdInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_AD_INFO_H_
