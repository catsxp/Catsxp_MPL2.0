/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/user_attention/user_idle_detection/user_idle_detection_feature.h"

namespace catsxp_ads {

BASE_FEATURE(kUserIdleDetectionFeature,
             "UserIdleDetection",
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace catsxp_ads
