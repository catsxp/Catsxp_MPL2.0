/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type_util.h"

#include <ostream>  // IWYU pragma: keep
#include <utility>

#include "base/notreached.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type_constants.h"

namespace catsxp_ads {

CreativeNewTabPageAdWallpaperType ToCreativeNewTabPageAdWallpaperType(
    std::string_view wallpaper_type) {
  if (wallpaper_type == kCreativeNewTabPageAdImageWallpaperType) {
    return CreativeNewTabPageAdWallpaperType::kImage;
  }

  if (wallpaper_type == kCreativeNewTabPageAdRichMediaWallpaperType) {
    return CreativeNewTabPageAdWallpaperType::kRichMedia;
  }

  NOTREACHED() << "Unexpected value for wallpaper_type: " << wallpaper_type;
}

std::string ToString(CreativeNewTabPageAdWallpaperType wallpaper_type) {
  switch (wallpaper_type) {
    case CreativeNewTabPageAdWallpaperType::kImage: {
      return kCreativeNewTabPageAdImageWallpaperType;
    }

    case CreativeNewTabPageAdWallpaperType::kRichMedia: {
      return kCreativeNewTabPageAdRichMediaWallpaperType;
    }

    default: {
      break;
    }
  }

  NOTREACHED() << "Unexpected value for CreativeNewTabPageAdWallpaperType: "
               << std::to_underlying(wallpaper_type);
}

}  // namespace catsxp_ads
