/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/dislike_exclusion_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_core/ads_core_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsDislikeExclusionRuleTest : public test::TestBase {
 protected:
  const DislikeExclusionRule exclusion_rule_;
};

TEST_F(CatsxpAdsDislikeExclusionRuleTest, ShouldIncludeForNeutralReaction) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.advertiser_id = test::kAdvertiserId;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsDislikeExclusionRuleTest, ShouldIncludeForLikedReaction) {
  // Arrange
  GetReactions().AdsForTesting() = {
      {test::kAdvertiserId, mojom::ReactionType::kLiked}};

  CreativeAdInfo creative_ad;
  creative_ad.advertiser_id = test::kAdvertiserId;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsDislikeExclusionRuleTest, ShouldExcludeForDislikedReaction) {
  // Arrange
  GetReactions().AdsForTesting() = {
      {test::kAdvertiserId, mojom::ReactionType::kDisliked}};

  CreativeAdInfo creative_ad;
  creative_ad.advertiser_id = test::kAdvertiserId;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

}  // namespace catsxp_ads
