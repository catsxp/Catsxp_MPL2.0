/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_events_database_table_util.h"

#include <optional>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

// npm run test -- catsxp_all_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database::table {

namespace {

mojom::DBRowInfoPtr BuildAdEventRow(const std::string& placement_id,
                                    const std::string& ad_type,
                                    const std::string& confirmation_type,
                                    const std::string& campaign_id,
                                    const std::string& creative_set_id,
                                    const std::string& creative_instance_id,
                                    const std::string& advertiser_id,
                                    const std::string& segment,
                                    const std::string& target_url,
                                    base::Time created_at) {
  auto mojom_db_row = mojom::DBRowInfo::New();
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(placement_id));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(ad_type));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(confirmation_type));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(campaign_id));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(creative_set_id));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(creative_instance_id));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(advertiser_id));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(segment));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewStringValue(target_url));
  mojom_db_row->column_values_union.push_back(
      mojom::DBColumnValueUnion::NewTimeValue(created_at));
  return mojom_db_row;
}

}  // namespace

class CatsxpAdsAdEventsDatabaseTableUtilTest : public ::testing::Test {};

TEST_F(CatsxpAdsAdEventsDatabaseTableUtilTest, MapAllFieldsFromMojomRow) {
  // Arrange
  const base::Time created_at =
      base::Time::FromSecondsSinceUnixEpoch(1'000'000.0);
  mojom::DBRowInfoPtr mojom_db_row = BuildAdEventRow(
      "placement-id", /*ad_type=*/"ad_notification",
      /*confirmation_type=*/"view", "campaign-id", "creative-set-id",
      "creative-instance-id", "advertiser-id", "segment",
      /*target_url=*/"https://example.com", created_at);

  // Act
  const AdEventInfo ad_event = AdEventFromMojomRow(mojom_db_row);

  // Assert
  EXPECT_THAT(ad_event,
              ::testing::FieldsAre(
                  mojom::AdType::kNotificationAd,
                  mojom::ConfirmationType::kViewedImpression, "placement-id",
                  "creative-instance-id", "creative-set-id", "campaign-id",
                  "advertiser-id", "segment",
                  /*target_url=*/GURL("https://example.com"), created_at));
}

TEST_F(CatsxpAdsAdEventsDatabaseTableUtilTest, NoCreatedAtWhenNull) {
  // Arrange
  mojom::DBRowInfoPtr mojom_db_row = BuildAdEventRow(
      "placement-id", /*ad_type=*/"ad_notification",
      /*confirmation_type=*/"view", "campaign-id", "creative-set-id",
      "creative-instance-id", "advertiser-id", "segment",
      /*target_url=*/"https://example.com", /*created_at=*/base::Time());

  // Act
  const AdEventInfo ad_event = AdEventFromMojomRow(mojom_db_row);

  // Assert
  EXPECT_THAT(ad_event,
              ::testing::FieldsAre(mojom::AdType::kNotificationAd,
                                   mojom::ConfirmationType::kViewedImpression,
                                   "placement-id", "creative-instance-id",
                                   "creative-set-id", "campaign-id",
                                   "advertiser-id", "segment",
                                   /*target_url=*/GURL("https://example.com"),
                                   /*created_at=*/std::nullopt));
}

}  // namespace catsxp_ads::database::table
