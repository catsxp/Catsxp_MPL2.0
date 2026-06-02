/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_tokens_database_table_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_all_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database::table {

namespace {

mojom::DBRowInfoPtr BuildPaymentTokenRow(
    const std::string& transaction_id,
    const std::string& unblinded_token_base64,
    const std::string& public_key_base64,
    const std::string& confirmation_type,
    const std::string& ad_type) {
  auto mojom_db_row = mojom::DBRowInfo::New();
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(transaction_id));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(unblinded_token_base64));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(public_key_base64));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(confirmation_type));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(ad_type));
  return mojom_db_row;
}

}  // namespace

class CatsxpAdsPaymentTokensDatabaseTableUtilTest : public ::testing::Test {};

TEST_F(CatsxpAdsPaymentTokensDatabaseTableUtilTest, MapAllFieldsFromMojomRow) {
  // Arrange
  mojom::DBRowInfoPtr mojom_db_row = BuildPaymentTokenRow(
      "transaction-id", cbr::test::kUnblindedTokenBase64,
      cbr::test::kPublicKeyBase64, /*confirmation_type=*/"view",
      /*ad_type=*/"ad_notification");

  // Act
  const PaymentTokenInfo payment_token = PaymentTokenFromMojomRow(mojom_db_row);

  // Assert
  EXPECT_THAT(payment_token,
              ::testing::FieldsAre(
                  "transaction-id",
                  cbr::UnblindedToken(cbr::test::kUnblindedTokenBase64),
                  cbr::PublicKey(cbr::test::kPublicKeyBase64),
                  mojom::ConfirmationType::kViewedImpression,
                  mojom::AdType::kNotificationAd));
}

}  // namespace catsxp_ads::database::table
