/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transactions_database_table_util.h"

#include <optional>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_all_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database::table {

namespace {

mojom::DBRowInfoPtr BuildTransactionRow(const std::string& id,
                                        base::Time created_at,
                                        const std::string& creative_instance_id,
                                        double value,
                                        const std::string& segment,
                                        const std::string& ad_type,
                                        const std::string& confirmation_type,
                                        base::Time reconciled_at) {
  auto mojom_db_row = mojom::DBRowInfo::New();
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(id));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewTimeValue(created_at));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(creative_instance_id));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewDoubleValue(value));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(segment));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(ad_type));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(confirmation_type));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewTimeValue(reconciled_at));
  return mojom_db_row;
}

}  // namespace

class CatsxpAdsTransactionsDatabaseTableUtilTest : public ::testing::Test {};

TEST_F(CatsxpAdsTransactionsDatabaseTableUtilTest, MapAllFieldsFromMojomRow) {
  // Arrange
  const base::Time created_at =
      base::Time::FromSecondsSinceUnixEpoch(1'000'000.0);
  const base::Time reconciled_at =
      base::Time::FromSecondsSinceUnixEpoch(2'000'000.0);
  mojom::DBRowInfoPtr mojom_db_row = BuildTransactionRow(
      "transaction-id", created_at, "creative-instance-id", 0.01, "segment",
      /*ad_type=*/"ad_notification", /*confirmation_type=*/"view",
      reconciled_at);

  // Act
  const TransactionInfo transaction = TransactionFromMojomRow(mojom_db_row);

  // Assert
  EXPECT_THAT(transaction,
              ::testing::FieldsAre(
                  "transaction-id", created_at, "creative-instance-id",
                  "segment", 0.01, mojom::AdType::kNotificationAd,
                  mojom::ConfirmationType::kViewedImpression, reconciled_at));
}

TEST_F(CatsxpAdsTransactionsDatabaseTableUtilTest,
       NoCreatedAtOrReconciledAtWhenNull) {
  // Arrange
  mojom::DBRowInfoPtr mojom_db_row = BuildTransactionRow(
      "transaction-id", /*created_at=*/base::Time(), "creative-instance-id",
      0.0, "segment", /*ad_type=*/"ad_notification",
      /*confirmation_type=*/"view", /*reconciled_at=*/base::Time());

  // Act
  const TransactionInfo transaction = TransactionFromMojomRow(mojom_db_row);

  // Assert
  EXPECT_THAT(transaction, ::testing::FieldsAre(
                               "transaction-id", /*created_at=*/std::nullopt,
                               "creative-instance-id", "segment", 0.0,
                               mojom::AdType::kNotificationAd,
                               mojom::ConfirmationType::kViewedImpression,
                               /*reconciled_at=*/std::nullopt));
}

}  // namespace catsxp_ads::database::table
