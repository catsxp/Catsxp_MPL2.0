/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/confirmation_tokens_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/test/confirmation_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConfirmationTokensPermissionRuleTest : public test::TestBase {};

TEST_F(CatsxpAdsConfirmationTokensPermissionRuleTest,
       ShouldAllowIfDoesNotExceedCap) {
  // Arrange
  test::RefillConfirmationTokens(/*count=*/10);

  // Act & Assert
  EXPECT_TRUE(HasConfirmationTokensPermission());
}

TEST_F(CatsxpAdsConfirmationTokensPermissionRuleTest,
       ShouldAllowIfUserHasNotJoinedCatsxpRewards) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_TRUE(HasConfirmationTokensPermission());
}

TEST_F(CatsxpAdsConfirmationTokensPermissionRuleTest,
       ShouldNotAllowIfNoConfirmationTokens) {
  // Act & Assert
  EXPECT_FALSE(HasConfirmationTokensPermission());
}

TEST_F(CatsxpAdsConfirmationTokensPermissionRuleTest,
       ShouldNotAllowIfExceedsCap) {
  // Arrange
  test::RefillConfirmationTokens(/*count=*/9);

  // Act & Assert
  EXPECT_FALSE(HasConfirmationTokensPermission());
}

}  // namespace catsxp_ads
