/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/user_data_builder/dynamic/confirmation_dynamic_user_data_builder.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/user_data_builder/test/confirmation_user_data_builder_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConfirmationDynamicUserDataBuilderTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    test::MockConfirmationUserData();

    AdvanceClockTo(test::TimeFromUTCString("November 18 2020 12:34:56.789"));
  }
};

TEST_F(CatsxpAdsConfirmationDynamicUserDataBuilderTest, BuildDynamicUserData) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "diagnosticId": "c1298fde-7fdb-401f-a3ce-0b58fe86e6e2",
                      "systemTimestamp": "2020-11-18T12:00:00.000Z"
                    })JSON"),
            BuildDynamicUserData());
}

TEST_F(CatsxpAdsConfirmationDynamicUserDataBuilderTest,
       DoNotBuildDynamicUserDataForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_THAT(BuildDynamicUserData(), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
