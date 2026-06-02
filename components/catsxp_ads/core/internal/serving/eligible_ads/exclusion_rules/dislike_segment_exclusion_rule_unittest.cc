/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/dislike_segment_exclusion_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_core/ads_core_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsDislikeSegmentExclusionRuleTest : public test::TestBase {
 protected:
  const DislikeSegmentExclusionRule exclusion_rule_;
};

TEST_F(CatsxpAdsDislikeSegmentExclusionRuleTest,
       ShouldIncludeForNeutralReaction) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.segment = test::kSegment;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsDislikeSegmentExclusionRuleTest, ShouldIncludeForLikedReaction) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {test::kSegment, mojom::ReactionType::kLiked}};

  CreativeAdInfo creative_ad;
  creative_ad.segment = test::kSegment;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsDislikeSegmentExclusionRuleTest,
       ShouldExcludeForDislikedReaction) {
  // Arrange
  GetReactions().SegmentsForTesting() = {
      {test::kSegment, mojom::ReactionType::kDisliked}};

  CreativeAdInfo creative_ad;
  creative_ad.segment = test::kSegment;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

}  // namespace catsxp_ads
