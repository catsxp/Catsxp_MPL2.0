/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/url_request_builders/create_reward_confirmation_url_request_builder_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transaction_test_constants.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCreateRewardConfirmationUrlRequestBuilderUtilTest, GetPath) {
  // Act & Assert
  EXPECT_EQ(
      R"(/v3/confirmation/8b742869-6e4a-490c-ac31-31b49130098a/eyJzaWduYXR1cmUiOiJkaXZoV2dkM2w0TVpZeG9NV1VwL096RnRnc1VBdXlxcEo4R0J5emp2TFBFWkMzUGo3alhucWFXUmVWbU83cU5FNzNkWThaSk5ZQVBCaTZFV2pGMWpFZz09IiwidCI6Ii9tZlRBQWpIcldtQWxMaUVrdGJxTlMvZHhvTVZkbnoxZXNvVnBsUVVzN3lHL2FwQXEySzZPZVNUNmxCVEtGSm1PcTdyVjhRYlkvREYySEZSTWN6L0pRPT0ifQ==)",
      BuildCreateRewardConfirmationUrlPath(
          test::kTransactionId,
          R"(eyJzaWduYXR1cmUiOiJkaXZoV2dkM2w0TVpZeG9NV1VwL096RnRnc1VBdXlxcEo4R0J5emp2TFBFWkMzUGo3alhucWFXUmVWbU83cU5FNzNkWThaSk5ZQVBCaTZFV2pGMWpFZz09IiwidCI6Ii9tZlRBQWpIcldtQWxMaUVrdGJxTlMvZHhvTVZkbnoxZXNvVnBsUVVzN3lHL2FwQXEySzZPZVNUNmxCVEtGSm1PcTdyVjhRYlkvREYySEZSTWN6L0pRPT0ifQ==)"));
}

}  // namespace catsxp_ads
