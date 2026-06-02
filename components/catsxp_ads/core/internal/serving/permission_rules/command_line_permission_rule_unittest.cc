/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/command_line_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCommandLinePermissionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsCommandLinePermissionRuleTest,
       ShouldAllowIfDidNotOverrideCommandLineSwitchesForProduction) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());

  GlobalState::GetInstance()->CommandLineSwitches().environment_type =
      mojom::EnvironmentType::kProduction;

  GlobalState::GetInstance()
      ->CommandLineSwitches()
      .did_override_from_command_line = false;

  // Act & Assert
  EXPECT_TRUE(HasCommandLinePermission());
}

TEST_F(CatsxpAdsCommandLinePermissionRuleTest,
       ShouldAllowIfDidNotOverrideCommandLineSwitchesForStaging) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());

  GlobalState::GetInstance()->CommandLineSwitches().environment_type =
      mojom::EnvironmentType::kStaging;

  GlobalState::GetInstance()
      ->CommandLineSwitches()
      .did_override_from_command_line = false;

  // Act & Assert
  EXPECT_TRUE(HasCommandLinePermission());
}

TEST_F(CatsxpAdsCommandLinePermissionRuleTest,
       ShouldNotAllowIfDidOverrideCommandLineSwitchesForProduction) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());

  GlobalState::GetInstance()->CommandLineSwitches().environment_type =
      mojom::EnvironmentType::kProduction;

  GlobalState::GetInstance()
      ->CommandLineSwitches()
      .did_override_from_command_line = true;

  // Act & Assert
  EXPECT_FALSE(HasCommandLinePermission());
}

TEST_F(CatsxpAdsCommandLinePermissionRuleTest,
       ShouldAllowIfDidOverrideCommandLineSwitchesForStaging) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());

  GlobalState::GetInstance()->CommandLineSwitches().environment_type =
      mojom::EnvironmentType::kStaging;

  GlobalState::GetInstance()
      ->CommandLineSwitches()
      .did_override_from_command_line = true;

  // Act & Assert
  EXPECT_TRUE(HasCommandLinePermission());
}

}  // namespace catsxp_ads
