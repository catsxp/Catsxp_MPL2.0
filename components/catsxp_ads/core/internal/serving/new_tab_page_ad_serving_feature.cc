/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/new_tab_page_ad_serving_feature.h"

namespace catsxp_ads {

BASE_FEATURE(kNewTabPageAdServingFeature,
             "NewTabPageAdServing",
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace catsxp_ads
