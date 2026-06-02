/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/catalog_user_data.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_util.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/test/catalog_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCatalogUserDataTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    SetCatalogId(test::kCatalogId);
  }
};

TEST_F(CatsxpAdsCatalogUserDataTest, BuildCatalogUserData) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "catalog": [
                        {
                          "id": "29e5c8bc0ba319069980bb390d8e8f9b58c05a20"
                        }
                      ]
                    })JSON"),
            BuildCatalogUserData());
}

TEST_F(CatsxpAdsCatalogUserDataTest,
       DoNotBuildCatalogUserDataForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_THAT(BuildCatalogUserData(), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
