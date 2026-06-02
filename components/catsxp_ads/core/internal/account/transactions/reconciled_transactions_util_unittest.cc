/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/reconciled_transactions_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transactions_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsReconciledTransactionsUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsReconciledTransactionsUtilTest,
       DidNotReconcileTransactionsThisMonthForNoTransactions) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  // Act & Assert
  EXPECT_FALSE(DidReconcileTransactionsThisMonth(/*transactions=*/{}));
}

TEST_F(CatsxpAdsReconciledTransactionsUtilTest,
       DidNotReconcileTransactionsPreviousMonthForNoTransactions) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  // Act & Assert
  EXPECT_FALSE(DidReconcileTransactionsPreviousMonth(/*transactions=*/{}));
}

TEST_F(CatsxpAdsReconciledTransactionsUtilTest, DidReconcileTransaction) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  const TransactionInfo transaction = test::BuildTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression, /*reconciled_at=*/test::Now(),
      /*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_TRUE(DidReconcileTransaction(transaction));
}

TEST_F(CatsxpAdsReconciledTransactionsUtilTest, DidNotReconcileTransaction) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_FALSE(DidReconcileTransaction(transaction));
}

TEST_F(CatsxpAdsReconciledTransactionsUtilTest,
       DidReconcileTransactionWithinDateRange) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  const TransactionInfo transaction = test::BuildTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression, /*reconciled_at=*/test::Now(),
      /*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_TRUE(DidReconcileTransactionWithinDateRange(
      transaction, /*from_time=*/test::DistantPast(), /*to_time=*/test::Now()));
}

TEST_F(CatsxpAdsReconciledTransactionsUtilTest,
       DidNotReconcileTransactionWhenBeforeDateRange) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  const TransactionInfo transaction = test::BuildTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression, /*reconciled_at=*/test::Now(),
      /*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_FALSE(DidReconcileTransactionWithinDateRange(
      transaction, /*from_time=*/test::Now() + base::Milliseconds(1),
      /*to_time=*/test::DistantFuture()));
}

TEST_F(CatsxpAdsReconciledTransactionsUtilTest,
       DidNotReconcileTransactionWhenAfterDateRange) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  const TransactionInfo transaction = test::BuildTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression, /*reconciled_at=*/test::Now(),
      /*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_FALSE(DidReconcileTransactionWithinDateRange(
      transaction, /*from_time=*/test::DistantPast(),
      /*to_time=*/test::Now() - base::Milliseconds(1)));
}

}  // namespace catsxp_ads
