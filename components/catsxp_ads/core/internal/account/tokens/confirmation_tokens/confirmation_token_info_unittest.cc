/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_token_info.h"

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/test/confirmation_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConfirmationTokenInfoTest : public test::TestBase {};

TEST_F(CatsxpAdsConfirmationTokenInfoTest, IsValid) {
  // Act & Assert
  EXPECT_TRUE(test::BuildConfirmationToken().IsValid());
}

TEST_F(CatsxpAdsConfirmationTokenInfoTest, IsNotValid) {
  // Arrange
  const ConfirmationTokenInfo confirmation_token;

  // Act & Assert
  EXPECT_FALSE(confirmation_token.IsValid());
}

}  // namespace catsxp_ads
