/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/test/creative_notification_ad_test_util.h"

#include "base/check_op.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/test/creative_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/test/segment_test_constants.h"

namespace catsxp_ads::test {

CreativeNotificationAdList BuildCreativeNotificationAds(size_t count) {
  CHECK_GT(count, 0U);

  CreativeNotificationAdList creative_ads;

  for (size_t i = 0; i < count; ++i) {
    CreativeNotificationAdInfo creative_ad = BuildCreativeNotificationAd(
        /*use_random_uuids=*/true);
    creative_ad.segment = kSegments[i % kSegments.size()];

    creative_ads.push_back(creative_ad);
  }

  return creative_ads;
}

CreativeNotificationAdInfo BuildCreativeNotificationAd(bool use_random_uuids) {
  const CreativeAdInfo creative_ad = BuildCreativeAd(use_random_uuids);
  CreativeNotificationAdInfo creative_notification_ad(creative_ad);

  creative_notification_ad.title = "Test Ad Title";
  creative_notification_ad.body = "Test Ad Body";

  return creative_notification_ad;
}

}  // namespace catsxp_ads::test
