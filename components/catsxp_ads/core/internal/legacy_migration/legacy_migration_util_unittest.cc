/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/legacy_migration/legacy_migration_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "testing/gmock/include/gmock/gmock.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsLegacyMigrationUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsLegacyMigrationUtilTest, DeleteFile) {
  // Arrange
  EXPECT_CALL(ads_client_mock_, Remove("foo.json", ::testing::_ /*callback=*/));

  // Act & Assert
  MaybeDeleteFile("foo.json");
}

}  // namespace catsxp_ads
