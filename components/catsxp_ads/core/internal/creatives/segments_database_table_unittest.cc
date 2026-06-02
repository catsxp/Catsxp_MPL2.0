/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/segments_database_table_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database::table {

TEST(CatsxpAdsSegmentsDatabaseTableTest, InsertEmptySegments) {
  // Arrange
  mojom::DBTransactionInfoPtr mojom_db_transaction =
      mojom::DBTransactionInfo::New();

  // Act
  InsertSegments(mojom_db_transaction, /*segments=*/{});

  // Assert
  EXPECT_THAT(mojom_db_transaction->actions, ::testing::IsEmpty());
}

TEST(CatsxpAdsSegmentsDatabaseTableTest, InsertSegments) {
  // Arrange
  mojom::DBTransactionInfoPtr mojom_db_transaction =
      mojom::DBTransactionInfo::New();

  // Act
  InsertSegments(mojom_db_transaction, /*segments=*/{{"foo", {"bar"}}});

  // Assert
  EXPECT_THAT(mojom_db_transaction->actions, ::testing::SizeIs(1));
}

}  // namespace catsxp_ads::database::table
