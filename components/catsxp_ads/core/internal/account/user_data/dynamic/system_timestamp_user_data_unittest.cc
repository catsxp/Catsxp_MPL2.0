/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/dynamic/system_timestamp_user_data.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSystemTimestampUserDataTest : public test::TestBase {};

TEST_F(CatsxpAdsSystemTimestampUserDataTest, BuildSystemTimestampUserData) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("November 18 2020 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "systemTimestamp": "2020-11-18T12:00:00.000Z"
                    })JSON"),
            BuildSystemTimestampUserData());
}

TEST_F(CatsxpAdsSystemTimestampUserDataTest,
       DoNotBuildSystemTimestampUserDataForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_THAT(BuildSystemTimestampUserData(), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
