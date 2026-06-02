/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_TEST_CREATIVE_NOTIFICATION_AD_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_TEST_CREATIVE_NOTIFICATION_AD_TEST_UTIL_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"

namespace catsxp_ads::test {

CreativeNotificationAdList BuildCreativeNotificationAds(size_t count);
CreativeNotificationAdInfo BuildCreativeNotificationAd(bool use_random_uuids);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_TEST_CREATIVE_NOTIFICATION_AD_TEST_UTIL_H_
