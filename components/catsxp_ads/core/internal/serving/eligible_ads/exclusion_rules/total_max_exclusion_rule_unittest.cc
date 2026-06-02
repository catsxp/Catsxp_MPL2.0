/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/total_max_exclusion_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/test/ad_event_builder_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsTotalMaxExclusionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsTotalMaxExclusionRuleTest, ShouldIncludeIfThereAreNoAdEvents) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;
  creative_ad.total_max = 2;

  const TotalMaxExclusionRule exclusion_rule(/*ad_events=*/{});

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsTotalMaxExclusionRuleTest, ShouldIncludeIfZero) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;
  creative_ad.total_max = 0;

  const TotalMaxExclusionRule exclusion_rule(/*ad_events=*/{});

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsTotalMaxExclusionRuleTest, ShouldIncludeIfDoesNotExceedCap) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;
  creative_ad.total_max = 2;

  AdEventList ad_events;
  const AdEventInfo ad_event =
      test::BuildAdEvent(creative_ad, mojom::AdType::kNotificationAd,
                         mojom::ConfirmationType::kServedImpression,
                         /*created_at=*/test::Now(), /*use_random_uuids=*/true);
  ad_events.push_back(ad_event);

  const TotalMaxExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsTotalMaxExclusionRuleTest,
       ShouldIncludeIfDoesNotExceedCapForNoMatchingCreatives) {
  // Arrange
  CreativeAdInfo creative_ad_1;
  creative_ad_1.creative_set_id = test::kCreativeSetId;
  creative_ad_1.total_max = 2;

  CreativeAdInfo creative_ad_2;
  creative_ad_2.creative_set_id = test::kAnotherCreativeSetId;

  AdEventList ad_events;
  const AdEventInfo ad_event = test::BuildAdEvent(
      creative_ad_2, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kServedImpression, /*created_at=*/test::Now(),
      /*use_random_uuids=*/true);
  ad_events.push_back(ad_event);
  ad_events.push_back(ad_event);

  const TotalMaxExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad_1));
}

TEST_F(CatsxpAdsTotalMaxExclusionRuleTest, ShouldExcludeIfExceedsCap) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;
  creative_ad.total_max = 2;

  AdEventList ad_events;
  const AdEventInfo ad_event =
      test::BuildAdEvent(creative_ad, mojom::AdType::kNotificationAd,
                         mojom::ConfirmationType::kServedImpression,
                         /*created_at=*/test::Now(), /*use_random_uuids=*/true);
  ad_events.push_back(ad_event);
  ad_events.push_back(ad_event);

  const TotalMaxExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_FALSE(exclusion_rule.ShouldInclude(creative_ad));
}

}  // namespace catsxp_ads
