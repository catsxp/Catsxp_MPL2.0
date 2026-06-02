/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/ads_util.h"

#include "base/test/scoped_command_line.h"
#include "catsxp/components/catsxp_ads/core/internal/common/locale/test/fake_locale.h"
#include "catsxp/components/catsxp_rewards/core/pref_names.h"
#include "catsxp/components/catsxp_rewards/core/rewards_flags.h"
#include "build/build_config.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/testing_pref_service.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsAdsUtilTest : public ::testing::Test {
  void SetUp() override {
    prefs_.registry()->RegisterBooleanPref(
        catsxp_rewards::prefs::kUseRewardsStagingServer, false);

    catsxp_rewards::RewardsFlags::SetForceParsingForTesting(true);
  }

 protected:
  test::FakeLocale fake_locale_;

  TestingPrefServiceSimple prefs_;

  base::test::ScopedCommandLine scoped_command_line_;
};

TEST_F(CatsxpAdsAdsUtilTest, UsesDefaultEnvironment) {
#if defined(OFFICIAL_BUILD)
  // In official builds, the default is production.
  EXPECT_FALSE(IsStagingEnvironment(prefs_));
#else
  // In non-official builds, the default is staging.
  EXPECT_TRUE(IsStagingEnvironment(prefs_));
#endif  // OFFICIAL_BUILD
}

TEST_F(CatsxpAdsAdsUtilTest, UsesStagingEnvironmentWhenEnabledFromCommandLine) {
  scoped_command_line_.GetProcessCommandLine()->AppendSwitchASCII(
      "rewards", "staging=true");
  EXPECT_TRUE(IsStagingEnvironment(prefs_));
}

TEST_F(CatsxpAdsAdsUtilTest, UsesProductionWhenDisabledFromCommandLine) {
  scoped_command_line_.GetProcessCommandLine()->AppendSwitchASCII(
      "rewards", "staging=false");
  EXPECT_FALSE(IsStagingEnvironment(prefs_));
}

#if BUILDFLAG(IS_ANDROID)
TEST_F(CatsxpAdsAdsUtilTest, UsesStagingWhenEnabledOnAndroid) {
  scoped_command_line_.GetProcessCommandLine()->AppendSwitchASCII(
      "rewards", "staging=false");
  prefs_.SetBoolean(catsxp_rewards::prefs::kUseRewardsStagingServer, true);
  EXPECT_TRUE(IsStagingEnvironment(prefs_));
}
#endif

TEST_F(CatsxpAdsAdsUtilTest, IsSupportedRegion) {
  // Arrange
  fake_locale_.SetCountryCode("US");

  // Act & Assert
  EXPECT_TRUE(IsSupportedRegion());
}

TEST_F(CatsxpAdsAdsUtilTest, IsUnsupportedRegion) {
  // Arrange
  fake_locale_.SetCountryCode(/*cuba*/ "CU");

  // Act & Assert
  EXPECT_FALSE(IsSupportedRegion());
}

}  // namespace catsxp_ads
