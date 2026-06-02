/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/zero_priority_exclusion_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsZeroPriorityExclusionRuleTest : public test::TestBase {
 protected:
  const ZeroPriorityExclusionRule exclusion_rule_;
};

TEST_F(CatsxpAdsZeroPriorityExclusionRuleTest,
       ShouldIncludeIfPriorityIsNonZero) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.priority = 1;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsZeroPriorityExclusionRuleTest, ShouldExcludeIfPriorityIsZero) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.priority = 0;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

}  // namespace catsxp_ads
