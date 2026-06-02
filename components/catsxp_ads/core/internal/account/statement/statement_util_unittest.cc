/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/statement/statement_util.h"

#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/account/statement/statement_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transactions_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsStatementUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsStatementUtilTest, MaybeGetNextPaymentDate) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("31 January 2020"));

  const base::Time next_payment_token_redemption_at =
      test::TimeFromUTCString("5 February 2020");
  test::SetProfileTimePrefValue(prefs::kNextPaymentTokenRedemptionAt,
                                next_payment_token_redemption_at);

  // Act
  const std::optional<base::Time> next_payment_date =
      MaybeGetNextPaymentDate(/*transactions=*/{});

  // Assert
  ASSERT_TRUE(next_payment_date);
  EXPECT_EQ(test::TimeFromUTCString("7 March 2020 23:59:59.999"),
            *next_payment_date);
}

TEST_F(CatsxpAdsStatementUtilTest, GetEstimatedEarningsForThisMonth) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  TransactionList transactions;

  const TransactionInfo transaction_1 = test::BuildUnreconciledTransaction(
      /*value=*/0.02, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_1);

  const TransactionInfo transaction_2 = test::BuildTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression, /*reconciled_at=*/test::Now(),
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_2);

  AdvanceClockTo(test::TimeFromString("25 December 2020"));

  const TransactionInfo transaction_3 = test::BuildUnreconciledTransaction(
      /*value=*/0.0, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kClicked,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_3);

  const TransactionInfo transaction_4 = test::BuildUnreconciledTransaction(
      /*value=*/0.03, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_4);

  const TransactionInfo transaction_5 = test::BuildUnreconciledTransaction(
      /*value=*/0.02, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_5);

  TransactionInfo transaction_6 = test::BuildUnreconciledTransaction(
      /*value=*/0.02, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transaction_6.ad_type = mojom::AdType::kNewTabPageAd;
  transactions.push_back(transaction_6);

  // Act
  const auto [min_estimated_earnings, max_estimated_earnings] =
      GetEstimatedEarningsForThisMonth(transactions);

  // Assert
  EXPECT_DOUBLE_EQ(0.07 * kMinEstimatedEarningsMultiplier.Get(),
                   min_estimated_earnings);
  EXPECT_DOUBLE_EQ(0.09, max_estimated_earnings);
}

TEST_F(CatsxpAdsStatementUtilTest, GetEstimatedEarningsForPreviousMonth) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  TransactionList transactions;

  const TransactionInfo transaction_1 = test::BuildTransaction(
      /*value=*/0.02, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression, /*reconciled_at=*/test::Now(),
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_1);

  TransactionInfo transaction_2 = test::BuildTransaction(
      /*value=*/0.02, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression, /*reconciled_at=*/test::Now(),
      /*use_random_uuids=*/true);
  transaction_2.ad_type = mojom::AdType::kNewTabPageAd;
  transactions.push_back(transaction_2);

  const TransactionInfo transaction_3 = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_3);

  AdvanceClockTo(test::TimeFromString("25 December 2020"));

  const TransactionInfo transaction_4 = test::BuildUnreconciledTransaction(
      /*value=*/0.0, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kClicked,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_4);

  const TransactionInfo transaction_5 = test::BuildTransaction(
      /*value=*/0.03, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression, /*reconciled_at=*/test::Now(),
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_5);

  // Act
  const auto [min_estimated_earnings, max_estimated_earnings] =
      GetEstimatedEarningsForPreviousMonth(transactions);

  // Assert
  EXPECT_DOUBLE_EQ(0.02 * kMinEstimatedEarningsMultiplier.Get(),
                   min_estimated_earnings);
  EXPECT_DOUBLE_EQ(0.04, max_estimated_earnings);
}

TEST_F(CatsxpAdsStatementUtilTest, GetAdsReceivedThisMonth) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  TransactionList transactions;

  const TransactionInfo transaction_1 = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_1);

  AdvanceClockTo(test::TimeFromString("25 December 2020"));

  const TransactionInfo transaction_2 = test::BuildUnreconciledTransaction(
      /*value=*/0.0, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kClicked,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_2);

  const TransactionInfo transaction_3 = test::BuildUnreconciledTransaction(
      /*value=*/0.03, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_3);

  const TransactionInfo transaction_4 = test::BuildUnreconciledTransaction(
      /*value=*/0.02, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_4);

  // Act & Assert
  EXPECT_EQ(2, GetAdsReceivedThisMonth(transactions));
}

TEST_F(CatsxpAdsStatementUtilTest, GetAdsSummaryThisMonth) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  TransactionList transactions;

  const TransactionInfo transaction_1 = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_1);

  AdvanceClockTo(test::TimeFromString("25 December 2020"));

  const TransactionInfo transaction_2 = test::BuildUnreconciledTransaction(
      /*value=*/0.0, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kClicked,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_2);

  const TransactionInfo transaction_3 = test::BuildUnreconciledTransaction(
      /*value=*/0.03, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_3);

  const TransactionInfo transaction_4 = test::BuildUnreconciledTransaction(
      /*value=*/0.02, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_4);

  // Act
  const base::flat_map<mojom::AdType, int32_t> ads_summary =
      GetAdsSummaryThisMonth(transactions);

  // Assert
  const base::flat_map<mojom::AdType, int32_t> expected_ads_summary = {
      {mojom::AdType::kNotificationAd, 2}};
  EXPECT_EQ(expected_ads_summary, ads_summary);
}

}  // namespace catsxp_ads
