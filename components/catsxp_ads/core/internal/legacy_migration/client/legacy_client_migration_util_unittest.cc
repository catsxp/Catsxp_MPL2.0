/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/legacy_migration/client/legacy_client_migration_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsLegacyClientMigrationUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsLegacyClientMigrationUtilTest, HasMigrated) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedClientState, true);

  // Act & Assert
  EXPECT_TRUE(HasMigratedClientState());
}

TEST_F(CatsxpAdsLegacyClientMigrationUtilTest, HasNotMigrated) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedClientState, false);

  // Act & Assert
  EXPECT_FALSE(HasMigratedClientState());
}

}  // namespace catsxp_ads
