/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_feature.h"

namespace catsxp_ads {

BASE_FEATURE(kNewTabPageAdFeature,
             "NewTabPageAds",
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace catsxp_ads
