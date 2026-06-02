/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/url_requests/request_signed_tokens/request_signed_tokens_url_request_builder_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/wallet/test/wallet_test_constants.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsRequestSignedTokensUrlRequestBuilderUtilTest, GetPath) {
  // Act & Assert
  EXPECT_EQ("/v3/confirmation/token/27a39b2f-9b2e-4eb0-bbb2-2f84447496e7",
            BuildRequestSignedTokensUrlPath(test::kWalletPaymentId));
}

}  // namespace catsxp_ads
