/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transactions_database_table.h"

#include "base/test/mock_callback.h"
#include "base/test/test_future.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transactions_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transactions_database_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database::table {

class CatsxpAdsTransactionsDatabaseTableTest : public test::TestBase {};

TEST_F(CatsxpAdsTransactionsDatabaseTableTest, SaveEmptyTransactions) {
  // Act
  SaveTransactions({});

  // Assert
  const Transactions database_table;
  base::test::TestFuture<bool, TransactionList> test_future;
  database_table.GetForDateRange(
      /*from_time=*/test::DistantPast(),
      /*to_time=*/test::DistantFuture(),
      test_future.GetCallback<bool, const TransactionList&>());
  const auto [success, transactions] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(transactions, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsTransactionsDatabaseTableTest, SaveTransactions) {
  // Arrange
  const TransactionInfo transaction_1 = test::BuildTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*reconciled_at=*/test::DistantFuture(),
      /*use_random_uuids=*/true);

  AdvanceClockBy(base::Days(5));

  const TransactionInfo transaction_2 = test::BuildUnreconciledTransaction(
      /*value=*/0.03, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kClicked,
      /*use_random_uuids=*/true);

  // Act
  SaveTransactions({transaction_1, transaction_2});

  // Assert
  const Transactions database_table;
  base::test::TestFuture<bool, TransactionList> test_future;
  database_table.GetForDateRange(
      /*from_time=*/test::DistantPast(),
      /*to_time=*/test::DistantFuture(),
      test_future.GetCallback<bool, const TransactionList&>());
  const auto [success, transactions] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(transactions,
              ::testing::ElementsAre(transaction_1, transaction_2));
}

TEST_F(CatsxpAdsTransactionsDatabaseTableTest, DoNotSaveDuplicateTransactions) {
  // Arrange
  const TransactionInfo transaction = test::BuildTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression, /*reconciled_at=*/test::Now(),
      /*use_random_uuids=*/true);

  SaveTransactions({transaction});

  // Act
  SaveTransactions({transaction});

  // Assert
  const Transactions database_table;
  base::test::TestFuture<bool, TransactionList> test_future;
  database_table.GetForDateRange(
      /*from_time=*/test::DistantPast(),
      /*to_time=*/test::DistantFuture(),
      test_future.GetCallback<bool, const TransactionList&>());
  const auto [success, transactions] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(transactions, ::testing::ElementsAre(transaction));
}

TEST_F(CatsxpAdsTransactionsDatabaseTableTest, GetTransactionsForDateRange) {
  // Arrange
  const TransactionInfo transaction_1 = test::BuildTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*reconciled_at=*/test::DistantFuture(),
      /*use_random_uuids=*/true);

  AdvanceClockBy(base::Days(5));

  const TransactionInfo transaction_2 = test::BuildUnreconciledTransaction(
      /*value=*/0.03, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kClicked,
      /*use_random_uuids=*/true);

  SaveTransactions({transaction_1, transaction_2});

  const Transactions database_table;

  // Act & Assert
  base::test::TestFuture<bool, TransactionList> test_future;
  database_table.GetForDateRange(
      /*from_time=*/test::Now(),
      /*to_time=*/test::DistantFuture(),
      test_future.GetCallback<bool, const TransactionList&>());
  const auto [success, transactions] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(transactions, ::testing::ElementsAre(transaction_2));
}

TEST_F(CatsxpAdsTransactionsDatabaseTableTest, ReconcileTransactions) {
  // Arrange
  const TransactionInfo transaction_1 = test::BuildTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*reconciled_at=*/test::DistantFuture(),
      /*use_random_uuids=*/true);

  TransactionInfo transaction_2 = test::BuildUnreconciledTransaction(
      /*value=*/0.03, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kClicked,
      /*use_random_uuids=*/true);

  SaveTransactions({transaction_1, transaction_2});

  PaymentTokenList payment_tokens;
  PaymentTokenInfo payment_token;
  payment_token.transaction_id = transaction_2.id;
  payment_tokens.push_back(payment_token);

  transaction_2.reconciled_at = test::Now();

  base::MockCallback<ResultCallback> reconcile_callback;
  EXPECT_CALL(reconcile_callback, Run(/*success=*/true));

  const Transactions database_table;

  // Act
  database_table.Reconcile(payment_tokens, reconcile_callback.Get());

  // Assert
  base::test::TestFuture<bool, TransactionList> test_future;
  database_table.GetForDateRange(
      /*from_time=*/test::DistantPast(),
      /*to_time=*/test::DistantFuture(),
      test_future.GetCallback<bool, const TransactionList&>());
  const auto [success, transactions] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(transactions, ::testing::UnorderedElementsAreArray(
                                TransactionList{transaction_1, transaction_2}));
}

TEST_F(CatsxpAdsTransactionsDatabaseTableTest, PurgeExpired) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("Tue, 19 Mar 2024 05:35"));

  const TransactionInfo transaction_1 = test::BuildTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*reconciled_at=*/test::DistantFuture(),
      /*use_random_uuids=*/true);

  AdvanceClockBy(base::Days(90));

  const TransactionInfo transaction_2 = test::BuildUnreconciledTransaction(
      /*value=*/0.03, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kClicked,
      /*use_random_uuids=*/true);

  const TransactionInfo transaction_3 = test::BuildTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*reconciled_at=*/test::DistantFuture(),
      /*use_random_uuids=*/true);

  SaveTransactions({transaction_1, transaction_2, transaction_3});

  const Transactions database_table;

  // Act & Assert
  base::MockCallback<ResultCallback> purge_expired_callback;
  EXPECT_CALL(purge_expired_callback, Run(/*success=*/true));
  database_table.PurgeExpired(purge_expired_callback.Get());

  base::test::TestFuture<bool, TransactionList> test_future;
  database_table.GetForDateRange(
      /*from_time=*/test::DistantPast(),
      /*to_time=*/test::DistantFuture(),
      test_future.GetCallback<bool, const TransactionList&>());
  const auto [success, transactions] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(transactions, ::testing::UnorderedElementsAreArray(
                                TransactionList{transaction_2, transaction_3}));
}

TEST_F(CatsxpAdsTransactionsDatabaseTableTest,
       DoNotPurgeExpiredOnTheCuspOfExpiration) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("Tue, 19 Mar 2024 05:35"));

  const TransactionInfo transaction_1 = test::BuildTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*reconciled_at=*/test::DistantFuture(),
      /*use_random_uuids=*/true);

  AdvanceClockBy(base::Days(90) - base::Milliseconds(1));

  const TransactionInfo transaction_2 = test::BuildTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kClicked,
      /*reconciled_at=*/test::DistantFuture(),
      /*use_random_uuids=*/true);

  SaveTransactions({transaction_1, transaction_2});

  const Transactions database_table;

  // Act & Assert
  base::MockCallback<ResultCallback> purge_expired_callback;
  EXPECT_CALL(purge_expired_callback, Run(/*success=*/true));
  database_table.PurgeExpired(purge_expired_callback.Get());

  base::test::TestFuture<bool, TransactionList> test_future;
  database_table.GetForDateRange(
      /*from_time=*/test::DistantPast(),
      /*to_time=*/test::DistantFuture(),
      test_future.GetCallback<bool, const TransactionList&>());
  const auto [success, transactions] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(transactions, ::testing::UnorderedElementsAreArray(
                                TransactionList{transaction_1, transaction_2}));
}

}  // namespace catsxp_ads::database::table
