/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_database_table_util.h"

#include <optional>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_all_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database::table {

namespace {

mojom::DBRowInfoPtr BuildCreativeSetConversionRow(
    const std::string& id,
    const std::string& url_pattern,
    int observation_window_days,
    base::Time expire_at) {
  auto mojom_db_row = mojom::DBRowInfo::New();
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(id));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(url_pattern));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewIntValue(observation_window_days));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewTimeValue(expire_at));
  return mojom_db_row;
}

}  // namespace

class CatsxpAdsCreativeSetConversionDatabaseTableUtilTest
    : public ::testing::Test {};

TEST_F(CatsxpAdsCreativeSetConversionDatabaseTableUtilTest,
       MapAllFieldsFromMojomRow) {
  // Arrange
  const base::Time expire_at =
      base::Time::FromSecondsSinceUnixEpoch(1'000'000.0);
  mojom::DBRowInfoPtr mojom_db_row =
      BuildCreativeSetConversionRow("creative-set-id", "https://example.com/*",
                                    /*observation_window_days=*/7, expire_at);

  // Act
  const CreativeSetConversionInfo creative_set_conversion =
      CreativeSetConversionFromMojomRow(mojom_db_row);

  // Assert
  EXPECT_THAT(creative_set_conversion,
              ::testing::FieldsAre("creative-set-id", "https://example.com/*",
                                   base::Days(7), expire_at));
}

TEST_F(CatsxpAdsCreativeSetConversionDatabaseTableUtilTest, NoExpireAtWhenNull) {
  // Arrange
  mojom::DBRowInfoPtr mojom_db_row = BuildCreativeSetConversionRow(
      "creative-set-id", "https://example.com/*",
      /*observation_window_days=*/14, /*expire_at=*/base::Time());

  // Act
  const CreativeSetConversionInfo creative_set_conversion =
      CreativeSetConversionFromMojomRow(mojom_db_row);

  // Assert
  EXPECT_THAT(creative_set_conversion,
              ::testing::FieldsAre("creative-set-id", "https://example.com/*",
                                   base::Days(14), /*expire_at=*/std::nullopt));
}

}  // namespace catsxp_ads::database::table
