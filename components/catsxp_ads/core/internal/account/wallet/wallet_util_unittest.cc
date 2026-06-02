/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/wallet/wallet_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/wallet/test/wallet_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/account/wallet/wallet_info.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsWalletUtilTest, MaybeBuildWalletFromRecoverySeed) {
  // Act
  std::optional<WalletInfo> wallet = MaybeBuildWalletFromRecoverySeed(
      test::kWalletPaymentId, test::kWalletRecoverySeedBase64);
  ASSERT_TRUE(wallet);

  // Assert
  EXPECT_THAT(*wallet, ::testing::FieldsAre(test::kWalletPaymentId,
                                            test::kWalletPublicKey,
                                            test::kWalletSecretKey));
}

TEST(CatsxpAdsWalletUtilTest, DoesNotBuildWalletFromInvalidRecoverySeed) {
  // Act & Assert
  EXPECT_FALSE(MaybeBuildWalletFromRecoverySeed(
      test::kWalletPaymentId, test::kInvalidWalletRecoverySeed));
}

}  // namespace catsxp_ads
