/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/anti_targeting_exclusion_rule.h"

#include <memory>
#include <string_view>

#include "base/test/run_until.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/resources/test/country_components_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/anti_targeting/resource/anti_targeting_resource.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {
constexpr std::string_view kAntiTargetedSite = "https://www.catsxp.com";
}  // namespace

class CatsxpAdsAntiTargetingExclusionRuleTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    resource_ = std::make_unique<AntiTargetingResource>();
  }

  std::unique_ptr<AntiTargetingResource> resource_;
};

TEST_F(CatsxpAdsAntiTargetingExclusionRuleTest,
       ShouldIncludeIfResourceIsNotInitialized) {
  // Arrange
  const AntiTargetingExclusionRule exclusion_rule(
      *resource_, /*site_history=*/{GURL(kAntiTargetedSite)});

  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsAntiTargetingExclusionRuleTest,
       ShouldIncludeIfNotVisitedAntiTargetedSiteForCreativeSet) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  const AntiTargetingExclusionRule exclusion_rule(
      *resource_, /*site_history=*/{GURL(kAntiTargetedSite)});

  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kMissingCreativeSetId;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsAntiTargetingExclusionRuleTest,
       ShouldIncludeIfNotVisitedAntiTargetedSite) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  const AntiTargetingExclusionRule exclusion_rule(
      *resource_, /*site_history=*/{GURL("https://www.foo.com")});

  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsAntiTargetingExclusionRuleTest,
       ShouldExcludeIfVisitedAntiTargetedSite) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  const AntiTargetingExclusionRule exclusion_rule(
      *resource_, /*site_history=*/{GURL(kAntiTargetedSite)});

  CreativeAdInfo creative_ad;
  creative_ad.creative_set_id = test::kCreativeSetId;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule.ShouldInclude(creative_ad));
}

}  // namespace catsxp_ads
