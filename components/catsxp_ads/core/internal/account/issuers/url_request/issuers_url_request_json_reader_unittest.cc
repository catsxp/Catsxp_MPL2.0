/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/url_request/issuers_url_request_json_reader.h"

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/test/issuers_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_constants.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsIssuersUrlRequestJsonReaderTest : public test::TestBase {};

TEST(CatsxpAdsSubdivisionUrlRequestJsonReaderUtilTest, ReadIssuers) {
  // Act & Assert
  const IssuersInfo expected_issuers = test::BuildIssuers();

  EXPECT_EQ(expected_issuers, json::reader::ReadIssuers(R"JSON(
    {
      "ping": 7200000,
      "issuers": [
        {
          "name": "confirmations",
          "publicKeys": [
            {
              "publicKey": "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=",
              "associatedValue": ""
            },
            {
              "publicKey": "QnShwT9vRebch3WDu28nqlTaNCU5MaOF1n4VV4Q3K1g=",
              "associatedValue": ""
            }
          ]
        },
        {
          "name": "payments",
          "publicKeys": [
            {
              "publicKey": "JiwFR2EU/Adf1lgox+xqOVPuc6a/rxdy/LguFG5eaXg=",
              "associatedValue": "0.0"
            },
            {
              "publicKey": "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=",
              "associatedValue": "0.1"
            }
          ]
        }
      ]
    })JSON"));
}

TEST(CatsxpAdsSubdivisionUrlRequestJsonReaderUtilTest,
     DoNotReadIssuersIfMalformedJson) {
  // Act & Assert
  EXPECT_FALSE(json::reader::ReadIssuers(test::kMalformedJson));
}

TEST(CatsxpAdsSubdivisionUrlRequestJsonReaderUtilTest,
     DoNotReadIssuersIfMissingPing) {
  // Act & Assert
  EXPECT_FALSE(json::reader::ReadIssuers(R"JSON(
    {
      "issuers": [
        {
          "name": "confirmations",
          "publicKeys": [
            {
              "publicKey": "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=",
              "associatedValue": ""
            },
            {
              "publicKey": "QnShwT9vRebch3WDu28nqlTaNCU5MaOF1n4VV4Q3K1g=",
              "associatedValue": ""
            }
          ]
        },
        {
          "name": "payments",
          "publicKeys": [
            {
              "publicKey": "JiwFR2EU/Adf1lgox+xqOVPuc6a/rxdy/LguFG5eaXg=",
              "associatedValue": "0.0"
            },
            {
              "publicKey": "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=",
              "associatedValue": "0.1"
            }
          ]
        }
      ]
    })JSON"));
}

TEST(CatsxpAdsSubdivisionUrlRequestJsonReaderUtilTest,
     DoNotReadIssuersIfMissingTokenIssuers) {
  // Act & Assert
  EXPECT_FALSE(json::reader::ReadIssuers(R"JSON(
    {
      "ping": 7200000
    })JSON"));
}

}  // namespace catsxp_ads
