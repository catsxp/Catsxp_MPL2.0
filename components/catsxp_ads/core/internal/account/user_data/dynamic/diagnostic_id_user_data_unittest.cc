/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/dynamic/diagnostic_id_user_data.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsDiagnosticIdUserDataTest : public test::TestBase {};

TEST_F(CatsxpAdsDiagnosticIdUserDataTest, BuildDiagnosticIdUserData) {
  // Arrange
  test::SetProfileStringPrefValue(prefs::kDiagnosticId, test::kDiagnosticId);

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "diagnosticId": "c1298fde-7fdb-401f-a3ce-0b58fe86e6e2"
                    })JSON"),
            BuildDiagnosticIdUserData());
}

TEST_F(CatsxpAdsDiagnosticIdUserDataTest,
       DoNotBuildDiagnosticIdUserDataForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  test::SetProfileStringPrefValue(prefs::kDiagnosticId, test::kDiagnosticId);

  // Act & Assert
  EXPECT_THAT(BuildDiagnosticIdUserData(), ::testing::IsEmpty());
}

TEST_F(CatsxpAdsDiagnosticIdUserDataTest,
       DoNotBuildDiagnosticUserDataIfDiagnosticIdIsInvalid) {
  // Arrange
  test::SetProfileStringPrefValue(prefs::kDiagnosticId, "INVALID");

  // Act & Assert
  EXPECT_THAT(BuildDiagnosticIdUserData(), ::testing::IsEmpty());
}

TEST_F(CatsxpAdsDiagnosticIdUserDataTest,
       DoNotBuildDiagnosticIdUserDataIfDiagnosticIdIsEmpty) {
  // Arrange
  test::SetProfileStringPrefValue(prefs::kDiagnosticId, "");

  // Act & Assert
  EXPECT_THAT(BuildDiagnosticIdUserData(), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
