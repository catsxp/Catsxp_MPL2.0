/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_tokens_database_table.h"

#include "base/test/test_future.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/test/confirmation_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "testing/gmock/include/gmock/gmock.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database::table {

class CatsxpAdsConfirmationTokensDatabaseTableTest : public test::TestBase {
 protected:
  ConfirmationTokens database_table_;
};

TEST_F(CatsxpAdsConfirmationTokensDatabaseTableTest,
       SaveEmptyConfirmationTokens) {
  // Act
  base::test::TestFuture<bool> save_test_future;
  database_table_.Save({}, save_test_future.GetCallback());
  ASSERT_TRUE(save_test_future.Take());

  // Assert
  base::test::TestFuture<bool, ConfirmationTokenList> get_all_test_future;
  database_table_.GetAll(
      get_all_test_future.GetCallback<bool, const ConfirmationTokenList&>());
  const auto [success, confirmation_tokens] = get_all_test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(confirmation_tokens, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsConfirmationTokensDatabaseTableTest, SaveConfirmationTokens) {
  // Act
  base::test::TestFuture<bool> save_test_future;
  database_table_.Save(test::BuildConfirmationTokens(/*count=*/7),
                       save_test_future.GetCallback());
  ASSERT_TRUE(save_test_future.Take());

  // Assert
  base::test::TestFuture<bool, ConfirmationTokenList> get_all_test_future;
  database_table_.GetAll(
      get_all_test_future.GetCallback<bool, const ConfirmationTokenList&>());
  const auto [success, confirmation_tokens] = get_all_test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ(test::BuildConfirmationTokens(/*count=*/7), confirmation_tokens);
}

TEST_F(CatsxpAdsConfirmationTokensDatabaseTableTest,
       SaveDuplicateConfirmationTokens) {
  // Arrange
  base::test::TestFuture<bool> save_test_future;
  database_table_.Save(test::BuildConfirmationTokens(/*count=*/1),
                       save_test_future.GetCallback());
  ASSERT_TRUE(save_test_future.Take());

  // Act
  base::test::TestFuture<bool> duplicate_test_future;
  database_table_.Save(test::BuildConfirmationTokens(/*count=*/1),
                       duplicate_test_future.GetCallback());
  ASSERT_TRUE(duplicate_test_future.Take());

  // Assert
  base::test::TestFuture<bool, ConfirmationTokenList> get_all_test_future;
  database_table_.GetAll(
      get_all_test_future.GetCallback<bool, const ConfirmationTokenList&>());
  const auto [success, confirmation_tokens] = get_all_test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ(test::BuildConfirmationTokens(/*count=*/1), confirmation_tokens);
}

TEST_F(CatsxpAdsConfirmationTokensDatabaseTableTest, DeleteConfirmationToken) {
  // Arrange
  base::test::TestFuture<bool> save_test_future;
  database_table_.Save(test::BuildConfirmationTokens(/*count=*/2),
                       save_test_future.GetCallback());
  ASSERT_TRUE(save_test_future.Take());

  // Act
  base::test::TestFuture<bool> delete_test_future;
  database_table_.Delete(test::BuildConfirmationTokens(/*count=*/2).front(),
                         delete_test_future.GetCallback());
  ASSERT_TRUE(delete_test_future.Take());

  // Assert
  base::test::TestFuture<bool, ConfirmationTokenList> get_all_test_future;
  database_table_.GetAll(
      get_all_test_future.GetCallback<bool, const ConfirmationTokenList&>());
  const auto [success, confirmation_tokens] = get_all_test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ((ConfirmationTokenList{
                test::BuildConfirmationTokens(/*count=*/2).back()}),
            confirmation_tokens);
}

TEST_F(CatsxpAdsConfirmationTokensDatabaseTableTest,
       DoNotDeleteMissingConfirmationToken) {
  // Arrange
  base::test::TestFuture<bool> save_test_future;
  database_table_.Save(test::BuildConfirmationTokens(/*count=*/1),
                       save_test_future.GetCallback());
  ASSERT_TRUE(save_test_future.Take());

  // Act
  base::test::TestFuture<bool> delete_test_future;
  database_table_.Delete(test::BuildConfirmationTokens(/*count=*/2).back(),
                         delete_test_future.GetCallback());
  ASSERT_TRUE(delete_test_future.Take());

  // Assert
  base::test::TestFuture<bool, ConfirmationTokenList> get_all_test_future;
  database_table_.GetAll(
      get_all_test_future.GetCallback<bool, const ConfirmationTokenList&>());
  const auto [success, confirmation_tokens] = get_all_test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ(test::BuildConfirmationTokens(/*count=*/1), confirmation_tokens);
}

TEST_F(CatsxpAdsConfirmationTokensDatabaseTableTest,
       DeleteAllConfirmationTokens) {
  // Arrange
  base::test::TestFuture<bool> save_test_future;
  database_table_.Save(test::BuildConfirmationTokens(/*count=*/7),
                       save_test_future.GetCallback());
  ASSERT_TRUE(save_test_future.Take());

  // Act
  base::test::TestFuture<bool> delete_all_test_future;
  database_table_.DeleteAll(delete_all_test_future.GetCallback());
  ASSERT_TRUE(delete_all_test_future.Take());

  // Assert
  base::test::TestFuture<bool, ConfirmationTokenList> get_all_test_future;
  database_table_.GetAll(
      get_all_test_future.GetCallback<bool, const ConfirmationTokenList&>());
  const auto [success, confirmation_tokens] = get_all_test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(confirmation_tokens, ::testing::IsEmpty());
}

}  // namespace catsxp_ads::database::table
