/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/campaigns_database_table.h"

#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/test/creative_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database::table {

TEST(CatsxpAdsCampaignsDatabaseTableTest, InsertEmptyCampaigns) {
  // Arrange
  mojom::DBTransactionInfoPtr mojom_db_transaction =
      mojom::DBTransactionInfo::New();
  Campaigns database_table;

  // Act
  database_table.Insert(mojom_db_transaction, /*creative_ads=*/{});

  // Assert
  EXPECT_THAT(mojom_db_transaction->actions, ::testing::IsEmpty());
}

TEST(CatsxpAdsCampaignsDatabaseTableTest, InsertCampaigns) {
  // Arrange
  mojom::DBTransactionInfoPtr mojom_db_transaction =
      mojom::DBTransactionInfo::New();
  Campaigns database_table;

  // Act
  database_table.Insert(mojom_db_transaction,
                        /*creative_ads=*/{test::BuildCreativeAd(false)});

  // Assert
  EXPECT_THAT(mojom_db_transaction->actions, ::testing::SizeIs(5));
}

}  // namespace catsxp_ads::database::table
