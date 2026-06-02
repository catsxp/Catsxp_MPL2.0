/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_value_util.h"

#include <string_view>

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/test/issuers_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

constexpr std::string_view kTokenIssuersAsJson = R"JSON(
  [
    {
      "name": "confirmations",
      "publicKeys": [
        {
          "publicKey": "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=",
          "associatedValue": "0"
        },
        {
          "publicKey": "QnShwT9vRebch3WDu28nqlTaNCU5MaOF1n4VV4Q3K1g=",
          "associatedValue": "0"
        }
      ]
    },
    {
      "name": "payments",
      "publicKeys": [
        {
          "publicKey": "JiwFR2EU/Adf1lgox+xqOVPuc6a/rxdy/LguFG5eaXg=",
          "associatedValue": "0"
        },
        {
          "publicKey": "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=",
          "associatedValue": "0.1"
        }
      ]
    }
  ])JSON";

}  // namespace

class CatsxpAdsTokenIssuerValueUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsTokenIssuerValueUtilTest, TokenIssuersToList) {
  // Arrange
  const TokenIssuerList token_issuers = test::BuildTokenIssuers();

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonList(kTokenIssuersAsJson),
            TokenIssuersToList(token_issuers));
}

TEST_F(CatsxpAdsTokenIssuerValueUtilTest, EmptyTokenIssuersToList) {
  EXPECT_THAT(TokenIssuersToList({}), ::testing::IsEmpty());
}

TEST_F(CatsxpAdsTokenIssuerValueUtilTest, MaybeBuildTokenIssuersFromList) {
  // Arrange
  const base::ListValue list = base::test::ParseJsonList(kTokenIssuersAsJson);

  // Act & Assert
  EXPECT_EQ(test::BuildTokenIssuers(), MaybeBuildTokenIssuersFromList(list));
}

TEST_F(CatsxpAdsTokenIssuerValueUtilTest, NoTokenIssuersFromEmptyList) {
  EXPECT_THAT(*MaybeBuildTokenIssuersFromList({}), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
