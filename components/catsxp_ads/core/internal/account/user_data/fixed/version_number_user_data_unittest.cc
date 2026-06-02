/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/version_number_user_data.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsVersionNumberUserDataTest : public test::TestBase {};

TEST_F(CatsxpAdsVersionNumberUserDataTest, BuildVersionNumberUserData) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "versionNumber": "1.2.0.0"
                    })JSON"),
            BuildVersionNumberUserData());
}

TEST_F(CatsxpAdsVersionNumberUserDataTest,
       BuildVersionNumberUserDataForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "versionNumber": "1.2.0.0"
                    })JSON"),
            BuildVersionNumberUserData());
}

}  // namespace catsxp_ads
