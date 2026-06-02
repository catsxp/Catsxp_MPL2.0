/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/statement/ads_received_util.h"

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transactions_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsAdsReceivedUtilTest : public test::TestBase {};

TEST_F(
    CatsxpAdsAdsReceivedUtilTest,
    GetAdsReceivedForDateRangeWhenUserHasJoinedCatsxpRewardsAndNotConnectedWallet) {
  // Arrange
  test::DisconnectExternalCatsxpRewardsWallet();

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

  const base::Time from_time = test::Now();

  AdvanceClockTo(test::TimeFromString("1 January 2021"));

  const TransactionInfo transaction_4 = test::BuildUnreconciledTransaction(
      /*value=*/0.02, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_4);

  TransactionInfo transaction_5 = test::BuildUnreconciledTransaction(
      /*value=*/0.02, mojom::AdType::kNewTabPageAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_5);

  // Act
  const size_t ads_received = GetAdsReceivedForDateRange(
      transactions, from_time, test::DistantFuture());

  // Assert
  EXPECT_EQ(3U, ads_received);
}

TEST_F(
    CatsxpAdsAdsReceivedUtilTest,
    GetAdsReceivedForDateRangeWhenUserHasJoinedCatsxpRewardsAndConnectedWallet) {
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

  const base::Time from_time = test::Now();

  AdvanceClockTo(test::TimeFromString("1 January 2021"));

  const TransactionInfo transaction_4 = test::BuildUnreconciledTransaction(
      /*value=*/0.02, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_4);

  TransactionInfo transaction_5 = test::BuildUnreconciledTransaction(
      /*value=*/0.02, mojom::AdType::kNewTabPageAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_5);

  // Act
  const size_t ads_received = GetAdsReceivedForDateRange(
      transactions, from_time, test::DistantFuture());

  // Assert
  EXPECT_EQ(3U, ads_received);
}

TEST_F(CatsxpAdsAdsReceivedUtilTest, DoNotGetAdsSummaryForDateRange) {
  // Arrange
  AdvanceClockTo(test::TimeFromString("5 November 2020"));

  TransactionList transactions;

  const TransactionInfo transaction_1 = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_1);

  const TransactionInfo transaction_2 = test::BuildUnreconciledTransaction(
      /*value=*/0.0, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kClicked,
      /*use_random_uuids=*/true);
  transactions.push_back(transaction_2);

  AdvanceClockTo(test::TimeFromString("1 January 2021"));

  // Act
  const size_t ads_received = GetAdsReceivedForDateRange(
      transactions, /*from_time=*/test::Now(), test::DistantFuture());

  // Assert
  EXPECT_EQ(0U, ads_received);
}

TEST_F(CatsxpAdsAdsReceivedUtilTest, GetAdsSummaryForNoTransactions) {
  // Act
  const size_t ads_received = GetAdsReceivedForDateRange(
      /*transactions=*/{}, test::DistantPast(), test::DistantFuture());

  // Assert
  EXPECT_EQ(0U, ads_received);
}

}  // namespace catsxp_ads
