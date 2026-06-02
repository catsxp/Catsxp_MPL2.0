/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/command_line_exclusion_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCommandLineExclusionRuleTest : public test::TestBase {
 protected:
  const CommandLineExclusionRule exclusion_rule_;
};

TEST_F(CatsxpAdsCommandLineExclusionRuleTest, ShouldIncludeCreativeInstance) {
  // Arrange
  GlobalState::GetInstance()->CommandLineSwitches().ads_uuids = {
      {test::kCreativeInstanceId, true},
  };

  CreativeAdInfo creative_ad;
  creative_ad.creative_instance_id = test::kCreativeInstanceId;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsCommandLineExclusionRuleTest, ShouldExcludeCreativeInstance) {
  // Arrange
  GlobalState::GetInstance()->CommandLineSwitches().ads_uuids = {
      {test::kAnotherCreativeInstanceId, true},
  };

  CreativeAdInfo creative_ad;
  creative_ad.creative_instance_id = test::kCreativeInstanceId;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsCommandLineExclusionRuleTest, ShouldIncludeCreativeSet) {
  // Arrange
  GlobalState::GetInstance()->CommandLineSwitches().ads_uuids = {
      {test::kCreativeSetId, true},
  };

  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsCommandLineExclusionRuleTest, ShouldExcludeCreativeSet) {
  // Arrange
  GlobalState::GetInstance()->CommandLineSwitches().ads_uuids = {
      {test::kAnotherCreativeSetId, true},
  };

  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsCommandLineExclusionRuleTest, ShouldIncludeCampaign) {
  // Arrange
  GlobalState::GetInstance()->CommandLineSwitches().ads_uuids = {
      {test::kCampaignId, true},
  };

  CreativeAdInfo creative_ad;
  creative_ad.campaign_id = test::kCampaignId;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsCommandLineExclusionRuleTest, ShouldExcludeCampaign) {
  // Arrange
  GlobalState::GetInstance()->CommandLineSwitches().ads_uuids = {
      {test::kAnotherCampaignId, true},
  };

  CreativeAdInfo creative_ad;
  creative_ad.campaign_id = test::kCampaignId;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsCommandLineExclusionRuleTest, ShouldIncludeAdvertiser) {
  // Arrange
  GlobalState::GetInstance()->CommandLineSwitches().ads_uuids = {
      {test::kAdvertiserId, true},
  };

  CreativeAdInfo creative_ad;
  creative_ad.advertiser_id = test::kAdvertiserId;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsCommandLineExclusionRuleTest, ShouldExcludeAdvertiser) {
  // Arrange
  GlobalState::GetInstance()->CommandLineSwitches().ads_uuids = {
      {test::kAnotherAdvertiserId, true},
  };

  CreativeAdInfo creative_ad;
  creative_ad.advertiser_id = test::kAdvertiserId;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

}  // namespace catsxp_ads
