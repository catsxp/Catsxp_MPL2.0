/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/non_reward/url_request_builders/create_non_reward_confirmation_url_request_builder_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transaction_test_constants.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCreateNonRewardConfirmationUrlRequestBuilderUtilTest, GetPath) {
  // Act & Assert
  EXPECT_EQ("/v4/confirmation/8b742869-6e4a-490c-ac31-31b49130098a",
            BuildCreateNonRewardConfirmationUrlPath(test::kTransactionId));
}

}  // namespace catsxp_ads
