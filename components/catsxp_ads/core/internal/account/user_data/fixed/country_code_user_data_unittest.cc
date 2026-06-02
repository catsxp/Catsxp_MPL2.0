/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/country_code_user_data.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCountryCodeUserDataTest : public test::TestBase {};

TEST_F(CatsxpAdsCountryCodeUserDataTest, BuildCountryCodeUserData) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "countryCode": "US"
                    })JSON"),
            BuildCountryCodeUserData());
}

TEST_F(CatsxpAdsCountryCodeUserDataTest,
       BuildCountryCodeUserDataForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "countryCode": "US"
                    })JSON"),
            BuildCountryCodeUserData());
}

}  // namespace catsxp_ads
