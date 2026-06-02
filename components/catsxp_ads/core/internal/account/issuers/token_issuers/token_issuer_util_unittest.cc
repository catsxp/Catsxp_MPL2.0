/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/test/issuers_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsTokenIssuerUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsTokenIssuerUtilTest, TokenIssuerExistsForConfirmationType) {
  // Arrange
  test::BuildAndSetIssuers();

  // Act & Assert
  EXPECT_TRUE(TokenIssuerExistsForType(TokenIssuerType::kConfirmations));
}

TEST_F(CatsxpAdsTokenIssuerUtilTest,
       TokenIssuerDoesNotExistForConfirmationType) {
  // Arrange
  const IssuersInfo issuers = test::BuildIssuers(
      /*ping=*/7'200'000, /*confirmation_token_issuer_public_keys=*/{},
      /*payment_token_issuer_public_keys=*/
      {{"JiwFR2EU/Adf1lgox+xqOVPuc6a/rxdy/LguFG5eaXg=", 0.0},
       {"OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=", 0.1}});

  SetIssuers(issuers);

  // Act & Assert
  EXPECT_FALSE(TokenIssuerExistsForType(TokenIssuerType::kConfirmations));
}

TEST_F(CatsxpAdsTokenIssuerUtilTest, TokenIssuerExistsForPaymentsType) {
  // Arrange
  test::BuildAndSetIssuers();

  // Act & Assert
  EXPECT_TRUE(TokenIssuerExistsForType(TokenIssuerType::kPayments));
}

TEST_F(CatsxpAdsTokenIssuerUtilTest, TokenIssuerDoesNotExistForPaymentsType) {
  // Arrange
  const IssuersInfo issuers = test::BuildIssuers(
      /*ping=*/7'200'000,
      /*confirmation_token_issuer_public_keys=*/
      {{"OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=", 0.0},
       {"cKo0rk1iS8Obgyni0X3RRoydDIGHsivTkfX/TM1Xl24=", 0.0}},
      /*payment_token_issuer_public_keys=*/{});

  SetIssuers(issuers);

  // Act & Assert
  EXPECT_FALSE(TokenIssuerExistsForType(TokenIssuerType::kPayments));
}

TEST_F(CatsxpAdsTokenIssuerUtilTest,
       TokenIssuerPublicKeyExistsForConfirmationsType) {
  // Arrange
  test::BuildAndSetIssuers();

  // Act & Assert
  EXPECT_TRUE(TokenIssuerPublicKeyExistsForType(
      TokenIssuerType::kConfirmations,
      cbr::PublicKey("QnShwT9vRebch3WDu28nqlTaNCU5MaOF1n4VV4Q3K1g=")));
}

TEST_F(CatsxpAdsTokenIssuerUtilTest,
       TokenIssuerPublicKeyDoesNotExistForConfirmationsType) {
  // Arrange
  test::BuildAndSetIssuers();

  // Act & Assert
  EXPECT_FALSE(TokenIssuerPublicKeyExistsForType(
      TokenIssuerType::kConfirmations,
      cbr::PublicKey("Nj2NZ6nJUsK5MJ9ga9tfyctxzpT+GlvENF2TRHU4kBg=")));
}

TEST_F(CatsxpAdsTokenIssuerUtilTest, TokenIssuerPublicKeyExistsForPaymentsType) {
  // Arrange
  test::BuildAndSetIssuers();

  // Act & Assert
  EXPECT_TRUE(TokenIssuerPublicKeyExistsForType(
      TokenIssuerType::kPayments,
      cbr::PublicKey("OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=")));
}

TEST_F(CatsxpAdsTokenIssuerUtilTest,
       TokenIssuerPublicKeyDoesNotExistForPaymentsType) {
  // Arrange
  test::BuildAndSetIssuers();

  // Act & Assert
  EXPECT_FALSE(TokenIssuerPublicKeyExistsForType(
      TokenIssuerType::kPayments,
      cbr::PublicKey("zNWjpwIbghgXvTol3XPLKV3NJoEFtvUoPMiKstiWm3A=")));
}

TEST_F(CatsxpAdsTokenIssuerUtilTest, GetTokenIssuerForType) {
  // Arrange
  const IssuersInfo issuers = test::BuildIssuers(
      /*ping=*/7'200'000,
      /*confirmation_token_issuer_public_keys=*/
      {{"OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=", 0.0},
       {"QnShwT9vRebch3WDu28nqlTaNCU5MaOF1n4VV4Q3K1g=", 0.0}},
      /*payment_token_issuer_public_keys=*/
      {{"JiwFR2EU/Adf1lgox+xqOVPuc6a/rxdy/LguFG5eaXg=", 0.0},
       {"OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=", 0.1}});

  // Act
  std::optional<TokenIssuerInfo> token_issuer =
      GetTokenIssuerForType(issuers, TokenIssuerType::kPayments);
  ASSERT_TRUE(token_issuer);

  // Assert
  EXPECT_THAT(*token_issuer,
              ::testing::FieldsAre(
                  TokenIssuerType::kPayments,
                  TokenIssuerPublicKeyMap{
                      {"JiwFR2EU/Adf1lgox+xqOVPuc6a/rxdy/LguFG5eaXg=", 0.0},
                      {"OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=", 0.1}}));
}

TEST_F(CatsxpAdsTokenIssuerUtilTest, DoNotGetTokenIssuerForMissingType) {
  // Arrange
  const IssuersInfo issuers = test::BuildIssuers(
      /*ping=*/7'200'000,
      /*confirmation_token_issuer_public_keys=*/
      {{"OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=", 0.0},
       {"QnShwT9vRebch3WDu28nqlTaNCU5MaOF1n4VV4Q3K1g=", 0.0}},
      /*payment_token_issuer_public_keys=*/{});

  // Act & Assert
  EXPECT_FALSE(GetTokenIssuerForType(issuers, TokenIssuerType::kPayments));
}

}  // namespace catsxp_ads
