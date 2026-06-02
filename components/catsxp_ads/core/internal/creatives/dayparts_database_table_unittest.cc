/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_daypart_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/dayparts_database_table_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database::table {

TEST(CatsxpAdsDayPartsDatabaseTableTest, InsertEmptyDayparts) {
  // Arrange
  mojom::DBTransactionInfoPtr mojom_db_transaction =
      mojom::DBTransactionInfo::New();

  // Act
  InsertDayparts(mojom_db_transaction, /*dayparts=*/{});

  // Assert
  EXPECT_THAT(mojom_db_transaction->actions, ::testing::IsEmpty());
}

TEST(CatsxpAdsDayPartsDatabaseTableTest, InsertDayparts) {
  // Arrange
  mojom::DBTransactionInfoPtr mojom_db_transaction =
      mojom::DBTransactionInfo::New();

  // Act
  InsertDayparts(mojom_db_transaction,
                 /*dayparts=*/{{"foo", {CreativeDaypartInfo{}}}});

  // Assert
  EXPECT_THAT(mojom_db_transaction->actions, ::testing::SizeIs(1));
}

}  // namespace catsxp_ads::database::table
