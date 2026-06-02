/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/legacy_migration/client/legacy_client_migration.h"

#include "base/test/mock_callback.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/legacy_migration/client/legacy_client_migration_util.h"
#include "catsxp/components/catsxp_ads/core/public/ads_constants.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {
constexpr char kLegacyClientMigrationJsonFilename[] =
    "legacy_client_migration.json";
}  // namespace

class CatsxpAdsLegacyClientMigrationTest : public test::TestBase {};

TEST_F(CatsxpAdsLegacyClientMigrationTest, Migrate) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedClientState, false);

  ASSERT_TRUE(CopyFileFromTestDataPathToProfilePath(
      kLegacyClientMigrationJsonFilename));

  // Act & Assert
  base::MockCallback<ResultCallback> callback;
  EXPECT_CALL(callback, Run(/*success=*/true));
  MigrateClientState(callback.Get());

  EXPECT_TRUE(HasMigratedClientState());
}

TEST_F(CatsxpAdsLegacyClientMigrationTest, AlreadyMigrated) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedClientState, true);

  ASSERT_TRUE(CopyFileFromTestDataPathToProfilePath(kClientJsonFilename));

  // Act & Assert
  base::MockCallback<ResultCallback> callback;
  EXPECT_CALL(callback, Run(/*success=*/true));
  MigrateClientState(callback.Get());

  EXPECT_TRUE(HasMigratedClientState());
}

TEST_F(CatsxpAdsLegacyClientMigrationTest, ResetMalformedClientState) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedClientState, false);

  ASSERT_TRUE(CopyFileFromTestDataPathToProfilePath(
      test::kMalformedJsonFilename, kClientJsonFilename));

  // Act & Assert
  base::MockCallback<ResultCallback> callback;
  EXPECT_CALL(callback, Run(/*success=*/true));
  MigrateClientState(callback.Get());

  EXPECT_TRUE(HasMigratedClientState());
}

}  // namespace catsxp_ads
