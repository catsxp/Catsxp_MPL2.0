/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/url_request_builders/fetch_payment_token_url_request_builder_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transaction_test_constants.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsFetchPaymentTokenUrlRequestBuilderUtilTest, GetPath) {
  // Act & Assert
  EXPECT_EQ(
      "/v3/confirmation/8b742869-6e4a-490c-ac31-31b49130098a/paymentToken",
      BuildFetchPaymentTokenUrlPath(test::kTransactionId));
}

}  // namespace catsxp_ads
