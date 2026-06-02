/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ads_database_table.h"

#include "base/test/test_future.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database::table {

class CatsxpAdsCreativeAdsDatabaseTableTest : public test::TestBase {};

TEST_F(CatsxpAdsCreativeAdsDatabaseTableTest,
       DoNotGetCreativeAdForMissingCreativeInstanceId) {
  // Act & Assert
  base::test::TestFuture<bool, std::string, CreativeAdInfo> test_future;
  const CreativeAds database_table;
  database_table.GetForCreativeInstanceId(
      test::kMissingCreativeInstanceId,
      test_future
          .GetCallback<bool, const std::string&, const CreativeAdInfo&>());
  const auto [success, creative_instance_id, creative_ad] = test_future.Take();
  EXPECT_FALSE(success);
}

}  // namespace catsxp_ads::database::table
