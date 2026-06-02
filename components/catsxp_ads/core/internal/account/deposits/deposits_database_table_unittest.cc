/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposits_database_table.h"

#include <optional>

#include "base/test/mock_callback.h"
#include "base/test/test_future.h"
#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposit_info.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database::table {

class CatsxpAdsDepositsDatabaseTableTest : public test::TestBase {};

TEST_F(CatsxpAdsDepositsDatabaseTableTest,
       DoNotGetDepositForMissingCreativeInstanceId) {
  // Act & Assert
  base::test::TestFuture<bool, std::optional<DepositInfo>> test_future;
  const Deposits database_table;
  database_table.GetForCreativeInstanceId(
      test::kMissingCreativeInstanceId,
      test_future.GetCallback<bool, std::optional<DepositInfo>>());
  const auto [success, deposit] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_FALSE(deposit);
}

TEST_F(CatsxpAdsDepositsDatabaseTableTest, SaveDeposit) {
  // Arrange
  DepositInfo deposit;
  deposit.creative_instance_id = test::kCreativeInstanceId;
  deposit.value = 1.0;
  deposit.expire_at = test::DistantFuture();

  // Act & Assert
  base::test::TestFuture<bool> test_future;
  Deposits database_table;
  database_table.Save(deposit, test_future.GetCallback());
  EXPECT_TRUE(test_future.Take());
}

TEST_F(CatsxpAdsDepositsDatabaseTableTest, GetDepositForCreativeInstanceId) {
  // Arrange
  DepositInfo deposit;
  deposit.creative_instance_id = test::kCreativeInstanceId;
  deposit.value = 1.0;
  deposit.expire_at = test::DistantFuture();

  base::MockCallback<ResultCallback> save_callback;
  EXPECT_CALL(save_callback, Run(/*success=*/true));
  Deposits database_table;
  database_table.Save(deposit, save_callback.Get());

  // Act & Assert
  base::test::TestFuture<bool, std::optional<DepositInfo>> test_future;
  database_table.GetForCreativeInstanceId(
      test::kCreativeInstanceId,
      test_future.GetCallback<bool, std::optional<DepositInfo>>());
  const auto [success, result] = test_future.Take();
  EXPECT_TRUE(success);
  ASSERT_TRUE(result);
  EXPECT_EQ(test::kCreativeInstanceId, result->creative_instance_id);
  EXPECT_DOUBLE_EQ(1.0, result->value);
}

}  // namespace catsxp_ads::database::table
