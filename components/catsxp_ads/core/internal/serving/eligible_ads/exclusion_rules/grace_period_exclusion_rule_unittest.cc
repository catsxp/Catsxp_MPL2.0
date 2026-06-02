/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/grace_period_exclusion_rule.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/local_state_pref_value_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/test/ad_event_builder_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {
constexpr base::TimeDelta kGracePeriod = base::Days(3);
}  // namespace

class CatsxpAdsGracePeriodExclusionRuleTest : public test::TestBase {
 protected:
  void SetUpMocks() override {
    test::SetLocalStateTimePrefValue(prefs::kFirstRunAt, base::Time::Now());
    test::SetProfileTimeDeltaPrefValue(prefs::kGracePeriod, kGracePeriod);
  }

  const GracePeriodExclusionRule exclusion_rule_;
};

TEST_F(CatsxpAdsGracePeriodExclusionRuleTest,
       ShouldIncludeIfWithinGracePeriodWhenDebugIsEnabled) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->CommandLineSwitches().should_debug = true;

  FastForwardClockBy(kGracePeriod - base::Milliseconds(1));

  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kDisabled;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsGracePeriodExclusionRuleTest,
       ShouldIncludeIfOutsideGracePeriodWhenDebugIsEnabled) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->CommandLineSwitches().should_debug = true;

  FastForwardClockBy(kGracePeriod);

  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kDisabled;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsGracePeriodExclusionRuleTest,
       ShouldIncludeIfWithinGracePeriodForDisabledMetrics) {
  // Arrange
  FastForwardClockBy(kGracePeriod - base::Milliseconds(1));

  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kDisabled;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsGracePeriodExclusionRuleTest,
       ShouldIncludeIfOutsideGracePeriodForDisabledMetrics) {
  // Arrange
  FastForwardClockBy(kGracePeriod);

  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kDisabled;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsGracePeriodExclusionRuleTest,
       ShouldExcludeIfWithinGracePeriodForConfirmationMetrics) {
  // Arrange
  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kConfirmation;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsGracePeriodExclusionRuleTest,
       ShouldExcludeIfWithinGracePeriodOnTheCuspForConfirmationMetrics) {
  // Arrange
  FastForwardClockBy(kGracePeriod - base::Milliseconds(1));

  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kConfirmation;

  // Act & Assert
  EXPECT_FALSE(exclusion_rule_.ShouldInclude(creative_ad));
}

TEST_F(CatsxpAdsGracePeriodExclusionRuleTest,
       ShouldIncludeIfOutsideGracePeriodForConfirmationMetrics) {
  // Arrange
  FastForwardClockBy(kGracePeriod);

  CreativeAdInfo creative_ad;
  creative_ad.metric_type = mojom::NewTabPageAdMetricType::kConfirmation;

  // Act & Assert
  EXPECT_TRUE(exclusion_rule_.ShouldInclude(creative_ad));
}

}  // namespace catsxp_ads
