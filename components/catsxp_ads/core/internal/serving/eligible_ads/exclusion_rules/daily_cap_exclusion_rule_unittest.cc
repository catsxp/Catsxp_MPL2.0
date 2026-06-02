/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/daily_cap_exclusion_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/test/ad_event_builder_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsDailyCapExclusionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsDailyCapExclusionRuleTest, ShouldIncludeIfThereAreNoAdEvents) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.campaign_id = test::kCampaignId;
  creative_ad.daily_cap = 2;

  const DailyCapExclusionRule exclusion_rule(/*ad_events=*/{});

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsDailyCapExclusionRuleTest, ShouldIncludeIfDoesNotExceedCap) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.campaign_id = test::kCampaignId;
  creative_ad.daily_cap = 2;

  AdEventList ad_events;
  const AdEventInfo ad_event =
      test::BuildAdEvent(creative_ad, mojom::AdType::kNotificationAd,
                         mojom::ConfirmationType::kServedImpression,
                         /*created_at=*/test::Now(), /*use_random_uuids=*/true);
  ad_events.push_back(ad_event);

  const DailyCapExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsDailyCapExclusionRuleTest,
       ShouldIncludeIfDoesNotExceedCapForNoMatchingCampaigns) {
  // Arrange
  CreativeAdInfo creative_ad_1;
  creative_ad_1.campaign_id = test::kCampaignId;
  creative_ad_1.daily_cap = 1;

  CreativeAdInfo creative_ad_2;
  creative_ad_2.campaign_id = test::kAnotherCampaignId;

  AdEventList ad_events;
  const AdEventInfo ad_event = test::BuildAdEvent(
      creative_ad_2, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kServedImpression, /*created_at=*/test::Now(),
      /*use_random_uuids=*/true);
  ad_events.push_back(ad_event);

  const DailyCapExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad_1));
}

TEST_F(CatsxpAdsDailyCapExclusionRuleTest,
       ShouldIncludeIfDoesNotExceedCapWithin1Day) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.campaign_id = test::kCampaignId;
  creative_ad.daily_cap = 2;

  AdEventList ad_events;
  const AdEventInfo ad_event =
      test::BuildAdEvent(creative_ad, mojom::AdType::kNotificationAd,
                         mojom::ConfirmationType::kServedImpression,
                         /*created_at=*/test::Now(), /*use_random_uuids=*/true);
  ad_events.push_back(ad_event);

  const DailyCapExclusionRule exclusion_rule(ad_events);

  AdvanceClockBy(base::Days(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsDailyCapExclusionRuleTest,
       ShouldIncludeIfDoesNotExceedCapAfter1Day) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.campaign_id = test::kCampaignId;
  creative_ad.daily_cap = 2;

  AdEventList ad_events;
  const AdEventInfo ad_event =
      test::BuildAdEvent(creative_ad, mojom::AdType::kNotificationAd,
                         mojom::ConfirmationType::kServedImpression,
                         /*created_at=*/test::Now(), /*use_random_uuids=*/true);
  ad_events.push_back(ad_event);

  const DailyCapExclusionRule exclusion_rule(ad_events);

  AdvanceClockBy(base::Days(1));

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsDailyCapExclusionRuleTest, ShouldExcludeIfExceedsCap) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.campaign_id = test::kCampaignId;
  creative_ad.daily_cap = 2;

  AdEventList ad_events;
  const AdEventInfo ad_event =
      test::BuildAdEvent(creative_ad, mojom::AdType::kNotificationAd,
                         mojom::ConfirmationType::kServedImpression,
                         /*created_at=*/test::Now(), /*use_random_uuids=*/true);
  ad_events.push_back(ad_event);
  ad_events.push_back(ad_event);

  const DailyCapExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_FALSE(exclusion_rule.ShouldInclude(creative_ad));
}

}  // namespace catsxp_ads
