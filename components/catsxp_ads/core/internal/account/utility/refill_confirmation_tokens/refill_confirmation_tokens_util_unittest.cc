/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/refill_confirmation_tokens_util.h"

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/test/confirmation_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/tokens_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsRefillConfirmationTokensUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsRefillConfirmationTokensUtilTest,
       ShouldRefillConfirmationTokens) {
  // Arrange
  const size_t count = kMinConfirmationTokens.Get() - 1;
  test::RefillConfirmationTokens(count);

  // Act & Assert
  EXPECT_TRUE(ShouldRefillConfirmationTokens());
}

TEST_F(CatsxpAdsRefillConfirmationTokensUtilTest,
       ShouldNotRefillConfirmationTokens) {
  // Arrange
  const size_t count = kMinConfirmationTokens.Get();
  test::RefillConfirmationTokens(count);

  // Act & Assert
  EXPECT_FALSE(ShouldRefillConfirmationTokens());
}

TEST_F(CatsxpAdsRefillConfirmationTokensUtilTest,
       CalculateAmountOfConfirmationTokensToRefill) {
  // Arrange
  test::RefillConfirmationTokens(/*count=*/10);

  // Act & Assert
  EXPECT_EQ(kMaxConfirmationTokens.Get() - 10,
            CalculateAmountOfConfirmationTokensToRefill());
}

}  // namespace catsxp_ads
