/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/priority/priority.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/test/creative_notification_ad_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsPriorityTest : public test::TestBase {};

TEST_F(CatsxpAdsPriorityTest,
       SortCreativeAdsIntoBucketsByPriorityForNoCreativeAds) {
  // Act
  const PrioritizedCreativeAdBuckets<CreativeAdList>
      prioritized_creative_ad_buckets =
          SortCreativeAdsIntoBucketsByPriority(CreativeAdList{});

  // Assert
  EXPECT_THAT(prioritized_creative_ad_buckets, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsPriorityTest,
       SortCreativeAdsIntoBucketsByPriorityForMultipleCreativeAds) {
  // Arrange
  CreativeNotificationAdList creative_ads;

  CreativeNotificationAdInfo creative_ad_1 =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_1.priority = 1;
  creative_ads.push_back(creative_ad_1);

  CreativeNotificationAdInfo creative_ad_2 =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_2.priority = 2;
  creative_ads.push_back(creative_ad_2);

  CreativeNotificationAdInfo creative_ad_3 =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_3.priority = 1;
  creative_ads.push_back(creative_ad_3);

  CreativeNotificationAdInfo creative_ad_4 =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_4.priority = 3;
  creative_ads.push_back(creative_ad_4);

  // Act
  const PrioritizedCreativeAdBuckets<CreativeNotificationAdList>
      prioritized_creative_ad_buckets =
          SortCreativeAdsIntoBucketsByPriority(creative_ads);

  // Assert
  const PrioritizedCreativeAdBuckets<CreativeNotificationAdList>
      expected_prioritized_creative_ad_buckets = {
          {/*priority=*/1, {creative_ad_1, creative_ad_3}},
          {/*priority=*/2, {creative_ad_2}},
          {/*priority=*/3, {creative_ad_4}}};
  EXPECT_THAT(expected_prioritized_creative_ad_buckets,
              ::testing::ElementsAreArray(prioritized_creative_ad_buckets));
}

TEST_F(CatsxpAdsPriorityTest,
       SortCreativeAdsIntoBucketsByPriorityForSingleCreativeAd) {
  // Arrange
  CreativeNotificationAdList creative_ads;

  CreativeNotificationAdInfo creative_ad_1 =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  creative_ad_1.priority = 3;
  creative_ads.push_back(creative_ad_1);

  // Act
  const PrioritizedCreativeAdBuckets<CreativeNotificationAdList>
      prioritized_creative_ad_buckets =
          SortCreativeAdsIntoBucketsByPriority(creative_ads);

  // Assert
  const PrioritizedCreativeAdBuckets<CreativeNotificationAdList>
      expected_prioritized_creative_ad_buckets = {
          {/*priority*/ 3, {creative_ad_1}}};
  EXPECT_THAT(expected_prioritized_creative_ad_buckets,
              prioritized_creative_ad_buckets);
}

}  // namespace catsxp_ads
