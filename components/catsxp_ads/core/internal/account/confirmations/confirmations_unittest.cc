/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmations.h"

#include <memory>

#include "base/test/test_future.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/confirmation_queue_database_table.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/test/confirmation_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/test/token_generator_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/test/transactions_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConfirmationsTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    confirmations_ = std::make_unique<Confirmations>();
  }

  std::unique_ptr<Confirmations> confirmations_;

  database::table::ConfirmationQueue confirmation_queue_database_table_;
};

TEST_F(CatsxpAdsConfirmationsTest, ConfirmForRewardsUser) {
  // Arrange
  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act
  confirmations_->Confirm(transaction, /*user_data=*/{});

  // Assert
  base::test::TestFuture<bool, ConfirmationQueueItemList> test_future;
  confirmation_queue_database_table_.GetAll(
      test_future.GetCallback<bool, const ConfirmationQueueItemList&>());
  const auto [success, confirmation_queue_items] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(confirmation_queue_items, ::testing::SizeIs(1));
}

TEST_F(CatsxpAdsConfirmationsTest, ConfirmForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const TransactionInfo transaction = test::BuildUnreconciledTransaction(
      /*value=*/0.01, mojom::AdType::kNotificationAd,
      mojom::ConfirmationType::kViewedImpression,
      /*use_random_uuids=*/false);

  // Act
  confirmations_->Confirm(transaction, /*user_data=*/{});

  // Assert
  base::test::TestFuture<bool, ConfirmationQueueItemList> test_future;
  confirmation_queue_database_table_.GetAll(
      test_future.GetCallback<bool, const ConfirmationQueueItemList&>());
  const auto [success, confirmation_queue_items] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(confirmation_queue_items, ::testing::SizeIs(1));
}

}  // namespace catsxp_ads
