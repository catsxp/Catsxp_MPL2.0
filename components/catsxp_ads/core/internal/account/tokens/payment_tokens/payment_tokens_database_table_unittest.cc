/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_tokens_database_table.h"

#include "base/test/test_future.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/test/payment_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "testing/gmock/include/gmock/gmock.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database::table {

class CatsxpAdsPaymentTokensDatabaseTableTest : public test::TestBase {
 protected:
  PaymentTokens database_table_;
};

TEST_F(CatsxpAdsPaymentTokensDatabaseTableTest, SaveEmptyPaymentTokens) {
  // Act
  base::test::TestFuture<bool> save_test_future;
  database_table_.Save({}, save_test_future.GetCallback());
  ASSERT_TRUE(save_test_future.Take());

  // Assert
  base::test::TestFuture<bool, PaymentTokenList> get_all_test_future;
  database_table_.GetAll(
      get_all_test_future.GetCallback<bool, const PaymentTokenList&>());
  const auto [success, payment_tokens] = get_all_test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(payment_tokens, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsPaymentTokensDatabaseTableTest, SavePaymentTokens) {
  // Arrange
  PaymentTokenInfo payment_token_1 = test::BuildPaymentToken();
  payment_token_1.transaction_id = "foo";
  PaymentTokenInfo payment_token_2 = test::BuildPaymentToken();
  payment_token_2.transaction_id = "bar";

  // Act
  base::test::TestFuture<bool> save_test_future;
  database_table_.Save({payment_token_1, payment_token_2},
                       save_test_future.GetCallback());
  ASSERT_TRUE(save_test_future.Take());

  // Assert
  base::test::TestFuture<bool, PaymentTokenList> get_all_test_future;
  database_table_.GetAll(
      get_all_test_future.GetCallback<bool, const PaymentTokenList&>());
  const auto [success, payment_tokens] = get_all_test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ((PaymentTokenList{payment_token_1, payment_token_2}),
            payment_tokens);
}

TEST_F(CatsxpAdsPaymentTokensDatabaseTableTest, SaveDuplicatePaymentTokens) {
  // Arrange
  const PaymentTokenInfo payment_token = test::BuildPaymentToken();
  base::test::TestFuture<bool> save_test_future;
  database_table_.Save({payment_token}, save_test_future.GetCallback());
  ASSERT_TRUE(save_test_future.Take());

  // Act
  base::test::TestFuture<bool> duplicate_test_future;
  database_table_.Save({payment_token}, duplicate_test_future.GetCallback());
  ASSERT_TRUE(duplicate_test_future.Take());

  // Assert
  base::test::TestFuture<bool, PaymentTokenList> get_all_test_future;
  database_table_.GetAll(
      get_all_test_future.GetCallback<bool, const PaymentTokenList&>());
  const auto [success, payment_tokens] = get_all_test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(payment_tokens, ::testing::SizeIs(1U));
}

TEST_F(CatsxpAdsPaymentTokensDatabaseTableTest, DeletePaymentToken) {
  // Arrange
  PaymentTokenInfo payment_token_1 = test::BuildPaymentToken();
  payment_token_1.transaction_id = "foo";
  PaymentTokenInfo payment_token_2 = test::BuildPaymentToken();
  payment_token_2.transaction_id = "bar";
  base::test::TestFuture<bool> save_test_future;
  database_table_.Save({payment_token_1, payment_token_2},
                       save_test_future.GetCallback());
  ASSERT_TRUE(save_test_future.Take());

  // Act
  base::test::TestFuture<bool> delete_test_future;
  database_table_.Delete(payment_token_1, delete_test_future.GetCallback());
  ASSERT_TRUE(delete_test_future.Take());

  // Assert
  base::test::TestFuture<bool, PaymentTokenList> get_all_test_future;
  database_table_.GetAll(
      get_all_test_future.GetCallback<bool, const PaymentTokenList&>());
  const auto [success, payment_tokens] = get_all_test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ((PaymentTokenList{payment_token_2}), payment_tokens);
}

TEST_F(CatsxpAdsPaymentTokensDatabaseTableTest, DeletePaymentTokens) {
  // Arrange
  PaymentTokenInfo payment_token_1 = test::BuildPaymentToken();
  payment_token_1.transaction_id = "foo";
  PaymentTokenInfo payment_token_2 = test::BuildPaymentToken();
  payment_token_2.transaction_id = "bar";
  PaymentTokenInfo payment_token_3 = test::BuildPaymentToken();
  payment_token_3.transaction_id = "baz";
  base::test::TestFuture<bool> save_test_future;
  database_table_.Save({payment_token_1, payment_token_2, payment_token_3},
                       save_test_future.GetCallback());
  ASSERT_TRUE(save_test_future.Take());

  // Act
  base::test::TestFuture<bool> delete_test_future;
  database_table_.Delete({payment_token_1, payment_token_2},
                         delete_test_future.GetCallback());
  ASSERT_TRUE(delete_test_future.Take());

  // Assert
  base::test::TestFuture<bool, PaymentTokenList> get_all_test_future;
  database_table_.GetAll(
      get_all_test_future.GetCallback<bool, const PaymentTokenList&>());
  const auto [success, payment_tokens] = get_all_test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ((PaymentTokenList{payment_token_3}), payment_tokens);
}

TEST_F(CatsxpAdsPaymentTokensDatabaseTableTest, DeleteEmptyPaymentTokens) {
  // Act & Assert
  base::test::TestFuture<bool> delete_test_future;
  database_table_.Delete(PaymentTokenList{}, delete_test_future.GetCallback());
  EXPECT_TRUE(delete_test_future.Take());
}

TEST_F(CatsxpAdsPaymentTokensDatabaseTableTest, DoNotDeleteMissingPaymentToken) {
  // Arrange
  PaymentTokenInfo payment_token = test::BuildPaymentToken();
  payment_token.transaction_id = "foo";
  base::test::TestFuture<bool> save_test_future;
  database_table_.Save({payment_token}, save_test_future.GetCallback());
  ASSERT_TRUE(save_test_future.Take());

  PaymentTokenInfo missing_payment_token = test::BuildPaymentToken();
  missing_payment_token.transaction_id = "bar";

  // Act
  base::test::TestFuture<bool> delete_test_future;
  database_table_.Delete(missing_payment_token,
                         delete_test_future.GetCallback());
  ASSERT_TRUE(delete_test_future.Take());

  // Assert
  base::test::TestFuture<bool, PaymentTokenList> get_all_test_future;
  database_table_.GetAll(
      get_all_test_future.GetCallback<bool, const PaymentTokenList&>());
  const auto [success, payment_tokens] = get_all_test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ((PaymentTokenList{payment_token}), payment_tokens);
}

TEST_F(CatsxpAdsPaymentTokensDatabaseTableTest, DeleteAllPaymentTokens) {
  // Arrange
  PaymentTokenInfo payment_token_1 = test::BuildPaymentToken();
  payment_token_1.transaction_id = "foo";
  PaymentTokenInfo payment_token_2 = test::BuildPaymentToken();
  payment_token_2.transaction_id = "bar";
  base::test::TestFuture<bool> save_test_future;
  database_table_.Save({payment_token_1, payment_token_2},
                       save_test_future.GetCallback());
  ASSERT_TRUE(save_test_future.Take());

  // Act
  base::test::TestFuture<bool> delete_all_test_future;
  database_table_.DeleteAll(delete_all_test_future.GetCallback());
  ASSERT_TRUE(delete_all_test_future.Take());

  // Assert
  base::test::TestFuture<bool, PaymentTokenList> get_all_test_future;
  database_table_.GetAll(
      get_all_test_future.GetCallback<bool, const PaymentTokenList&>());
  const auto [success, payment_tokens] = get_all_test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(payment_tokens, ::testing::IsEmpty());
}

}  // namespace catsxp_ads::database::table
