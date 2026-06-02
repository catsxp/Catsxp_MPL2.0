/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/conversion_exclusion_rule.h"

#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/test/ad_event_builder_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConversionExclusionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsConversionExclusionRuleTest,
       ShouldIncludeIfThereIsNoConversionHistory) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kExclusionRulesFeature);

  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;

  const ConversionExclusionRule exclusion_rule(/*ad_events=*/{});

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsConversionExclusionRuleTest,
       ShouldExcludeIfSameCreativeSetHasAlreadyConverted) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kExclusionRulesFeature,
      {{"should_exclude_ad_if_creative_set_exceeds_conversion_cap", "1"}});

  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;

  AdEventList ad_events;
  const AdEventInfo ad_event = test::BuildAdEvent(
      creative_ad, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kConversion,
      /*created_at=*/test::Now(), /*use_random_uuids=*/false);
  ad_events.push_back(ad_event);

  const ConversionExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_FALSE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsConversionExclusionRuleTest,
       ShouldAlwaysIncludeIfConversionCapIsSetToZero) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kExclusionRulesFeature,
      {{"should_exclude_ad_if_creative_set_exceeds_conversion_cap", "0"}});

  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;

  AdEventList ad_events;
  const AdEventInfo ad_event = test::BuildAdEvent(
      creative_ad, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kConversion,
      /*created_at=*/test::Now(), /*use_random_uuids=*/false);
  ad_events.push_back(ad_event);
  ad_events.push_back(ad_event);
  ad_events.push_back(ad_event);

  const ConversionExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsConversionExclusionRuleTest,
       ShouldIncludeIfNotExceededConversionCap) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kExclusionRulesFeature,
      {{"should_exclude_ad_if_creative_set_exceeds_conversion_cap", "7"}});

  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;

  AdEventList ad_events;
  const AdEventInfo ad_event = test::BuildAdEvent(
      creative_ad, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kConversion,
      /*created_at=*/test::Now(), /*use_random_uuids=*/false);
  for (size_t i = 0;
       i < kShouldExcludeAdIfCreativeSetExceedsConversionCap.Get() - 1; ++i) {
    ad_events.push_back(ad_event);
  }

  const ConversionExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsConversionExclusionRuleTest,
       ShouldExcludeIfExceededConversionCap) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kExclusionRulesFeature,
      {{"should_exclude_ad_if_creative_set_exceeds_conversion_cap", "7"}});

  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;

  AdEventList ad_events;
  const AdEventInfo ad_event = test::BuildAdEvent(
      creative_ad, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kConversion,
      /*created_at=*/test::Now(), /*use_random_uuids=*/false);
  for (size_t i = 0;
       i < kShouldExcludeAdIfCreativeSetExceedsConversionCap.Get(); ++i) {
    ad_events.push_back(ad_event);
  }

  const ConversionExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_FALSE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsConversionExclusionRuleTest,
       ShouldIncludeIfCreativeSetHasNotAlreadyConverted) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kExclusionRulesFeature,
      {{"should_exclude_ad_if_creative_set_exceeds_conversion_cap", "1"}});

  CreativeAdInfo creative_ad_1;
  creative_ad_1.creative_set_id = test::kCreativeSetId;

  CreativeAdInfo creative_ad_2;
  creative_ad_2.creative_set_id = test::kAnotherCreativeSetId;

  AdEventList ad_events;
  const AdEventInfo ad_event = test::BuildAdEvent(
      creative_ad_2, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kConversion,
      /*created_at=*/test::Now(), /*use_random_uuids=*/false);
  ad_events.push_back(ad_event);

  const ConversionExclusionRule exclusion_rule(ad_events);

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad_1));
}

}  // namespace catsxp_ads
