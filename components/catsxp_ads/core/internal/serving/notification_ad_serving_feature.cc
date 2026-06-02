/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/notification_ad_serving_feature.h"

namespace catsxp_ads {

BASE_FEATURE(kNotificationAdServingFeature,
             "NotificationAdServing",
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace catsxp_ads
