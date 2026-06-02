/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ads_database_table.h"

#include "base/test/test_future.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_environment_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/test/creative_new_tab_page_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest : public test::TestBase {
 protected:
  database::table::CreativeNewTabPageAds database_table_;
};

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest, SaveEmpty) {
  // Act
  test::SaveCreativeNewTabPageAds({});

  // Assert
  base::test::TestFuture<bool, SegmentList, CreativeNewTabPageAdList>
      test_future;
  database_table_.GetForActiveCampaigns(
      test_future
          .GetCallback<bool, const SegmentList&, CreativeNewTabPageAdList>());
  const auto [success, segments, creative_ads] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(segments, ::testing::IsEmpty());
  EXPECT_THAT(creative_ads, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest, Save) {
  // Arrange
  const CreativeNewTabPageAdList saved_creative_ads =
      test::BuildCreativeNewTabPageAds(
          CreativeNewTabPageAdWallpaperType::kImage, /*count=*/2);

  // Act
  test::SaveCreativeNewTabPageAds(saved_creative_ads);

  // Assert
  base::test::TestFuture<bool, SegmentList, CreativeNewTabPageAdList>
      test_future;
  database_table_.GetForActiveCampaigns(
      test_future
          .GetCallback<bool, const SegmentList&, CreativeNewTabPageAdList>());
  const auto [success, segments, creative_ads] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ((SegmentList{"architecture", "arts & entertainment"}), segments);
  EXPECT_THAT(creative_ads,
              ::testing::UnorderedElementsAreArray(saved_creative_ads));
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest, SaveInBatches) {
  // Arrange
  database_table_.SetBatchSize(2);

  const CreativeNewTabPageAdList saved_creative_ads =
      test::BuildCreativeNewTabPageAds(
          CreativeNewTabPageAdWallpaperType::kImage, /*count=*/3);

  // Act
  test::SaveCreativeNewTabPageAds(saved_creative_ads);

  // Assert
  base::test::TestFuture<bool, SegmentList, CreativeNewTabPageAdList>
      test_future;
  database_table_.GetForActiveCampaigns(
      test_future
          .GetCallback<bool, const SegmentList&, CreativeNewTabPageAdList>());
  const auto [success, segments, creative_ads] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ((SegmentList{"architecture", "arts & entertainment", "automotive"}),
            segments);
  EXPECT_THAT(creative_ads,
              ::testing::UnorderedElementsAreArray(saved_creative_ads));
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest, DoNotSaveDuplicates) {
  // Arrange
  const CreativeNewTabPageAdList saved_creative_ads =
      test::BuildCreativeNewTabPageAds(
          CreativeNewTabPageAdWallpaperType::kImage, /*count=*/1);
  test::SaveCreativeNewTabPageAds(saved_creative_ads);

  // Act
  test::SaveCreativeNewTabPageAds(saved_creative_ads);

  // Assert
  base::test::TestFuture<bool, SegmentList, CreativeNewTabPageAdList>
      test_future;
  database_table_.GetForActiveCampaigns(
      test_future
          .GetCallback<bool, const SegmentList&, CreativeNewTabPageAdList>());
  const auto [success, segments, creative_ads] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ(SegmentList{"architecture"}, segments);
  EXPECT_THAT(creative_ads,
              ::testing::UnorderedElementsAreArray(saved_creative_ads));
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest, GetForImageSegments) {
  // Arrange
  CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);
  creative_ad_1.segment = "food & drink";

  CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);
  creative_ad_2.segment = "technology & computing";

  test::SaveCreativeNewTabPageAds({creative_ad_1, creative_ad_2});

  // Act & Assert
  base::test::TestFuture<bool, SegmentList, CreativeNewTabPageAdList>
      test_future;
  database_table_.GetForSegments(
      /*segments=*/{"food & drink"},
      test_future
          .GetCallback<bool, const SegmentList&, CreativeNewTabPageAdList>());
  const auto [success, segments, creative_ads] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ(SegmentList{"food & drink"}, segments);
  EXPECT_THAT(creative_ads, ::testing::ElementsAre(creative_ad_1));
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest,
       GetForSegmentsIfTypeIsRichMedia) {
  // Arrange
  CreativeNewTabPageAdInfo creative_ad_1 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*use_random_uuids=*/true);
  creative_ad_1.segment = "food & drink";

  CreativeNewTabPageAdInfo creative_ad_2 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*use_random_uuids=*/true);
  creative_ad_2.segment = "technology & computing";

  test::SaveCreativeNewTabPageAds({creative_ad_1, creative_ad_2});

  // Act & Assert
  base::test::TestFuture<bool, SegmentList, CreativeNewTabPageAdList>
      test_future;
  database_table_.GetForSegments(
      /*segments=*/{"food & drink"},
      test_future
          .GetCallback<bool, const SegmentList&, CreativeNewTabPageAdList>());
  const auto [success, segments, creative_ads] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ(SegmentList{"food & drink"}, segments);
  EXPECT_THAT(creative_ads, ::testing::ElementsAre(creative_ad_1));
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest,
       DoNotGetForSegmentsIfTypeIsRichMediaAndJavascriptIsDisabled) {
  // Arrange
  test::SetUpAllowJavaScript(false);

  CreativeNewTabPageAdInfo creative_ad_1 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*use_random_uuids=*/true);
  creative_ad_1.segment = "food & drink";

  CreativeNewTabPageAdInfo creative_ad_2 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*use_random_uuids=*/true);
  creative_ad_2.segment = "technology & computing";

  test::SaveCreativeNewTabPageAds({creative_ad_1, creative_ad_2});

  // Act & Assert
  base::test::TestFuture<bool, SegmentList, CreativeNewTabPageAdList>
      test_future;
  database_table_.GetForSegments(
      /*segments=*/{"food & drink"},
      test_future
          .GetCallback<bool, const SegmentList&, CreativeNewTabPageAdList>());
  const auto [success, segments, creative_ads] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ(SegmentList{"food & drink"}, segments);
  EXPECT_THAT(creative_ads, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest,
       DoNotGetForEmptySegments) {
  // Arrange
  const CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);

  const CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(
          CreativeNewTabPageAdWallpaperType::kRichMedia,
          /*use_random_uuids=*/true);

  test::SaveCreativeNewTabPageAds({creative_ad_1, creative_ad_2});

  // Act & Assert
  base::test::TestFuture<bool, SegmentList, CreativeNewTabPageAdList>
      test_future;
  database_table_.GetForSegments(
      /*segments=*/{},
      test_future
          .GetCallback<bool, const SegmentList&, CreativeNewTabPageAdList>());
  const auto [success, segments, creative_ads] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(segments, ::testing::IsEmpty());
  EXPECT_THAT(creative_ads, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest,
       DoNotGetForMissingSegment) {
  // Arrange
  const CreativeNewTabPageAdList saved_creative_ads =
      test::BuildCreativeNewTabPageAds(
          CreativeNewTabPageAdWallpaperType::kImage, /*count=*/1);
  test::SaveCreativeNewTabPageAds(saved_creative_ads);

  // Act & Assert
  base::test::TestFuture<bool, SegmentList, CreativeNewTabPageAdList>
      test_future;
  database_table_.GetForSegments(
      /*segments=*/{"MISSING"},
      test_future
          .GetCallback<bool, const SegmentList&, CreativeNewTabPageAdList>());
  const auto [success, segments, creative_ads] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ(SegmentList{"MISSING"}, segments);
  EXPECT_THAT(creative_ads, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest, GetForMultipleSegments) {
  // Arrange
  CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);
  creative_ad_1.segment = "technology & computing";

  CreativeNewTabPageAdInfo creative_ad_2 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*use_random_uuids=*/true);
  creative_ad_2.segment = "food & drink";

  CreativeNewTabPageAdInfo creative_ad_3 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);
  creative_ad_3.segment = "automotive";

  test::SaveCreativeNewTabPageAds(
      {creative_ad_1, creative_ad_2, creative_ad_3});

  // Act & Assert
  base::test::TestFuture<bool, SegmentList, CreativeNewTabPageAdList>
      test_future;
  database_table_.GetForSegments(
      /*segments=*/{"technology & computing", "food & drink"},
      test_future
          .GetCallback<bool, const SegmentList&, CreativeNewTabPageAdList>());
  const auto [success, segments, creative_ads] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ((SegmentList{"technology & computing", "food & drink"}), segments);
  EXPECT_THAT(creative_ads,
              ::testing::UnorderedElementsAre(creative_ad_1, creative_ad_2));
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest,
       GetForCreativeInstanceIdIfTypeIsImage) {
  // Arrange
  const CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);

  const CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);

  test::SaveCreativeNewTabPageAds({creative_ad_1, creative_ad_2});

  // Act & Assert
  base::test::TestFuture<bool, std::string, CreativeNewTabPageAdInfo>
      test_future;
  database_table_.GetForCreativeInstanceId(
      creative_ad_1.creative_instance_id,
      test_future.GetCallback<bool, const std::string&,
                              const CreativeNewTabPageAdInfo&>());
  const auto [success, creative_instance_id, creative_ad] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ(creative_ad_1.creative_instance_id, creative_instance_id);
  EXPECT_EQ(creative_ad_1, creative_ad);
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest,
       GetForCreativeInstanceIdIfTypeIsImageAndJavascriptIsDisabled) {
  // Arrange
  test::SetUpAllowJavaScript(false);

  const CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);

  const CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);

  test::SaveCreativeNewTabPageAds({creative_ad_1, creative_ad_2});

  // Act & Assert
  base::test::TestFuture<bool, std::string, CreativeNewTabPageAdInfo>
      test_future;
  database_table_.GetForCreativeInstanceId(
      creative_ad_1.creative_instance_id,
      test_future.GetCallback<bool, const std::string&,
                              const CreativeNewTabPageAdInfo&>());
  const auto [success, creative_instance_id, creative_ad] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ(creative_ad_1.creative_instance_id, creative_instance_id);
  EXPECT_EQ(creative_ad_1, creative_ad);
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest,
       GetForCreativeInstanceIdIfTypeIsRichMedia) {
  // Arrange
  const CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(
          CreativeNewTabPageAdWallpaperType::kRichMedia,
          /*use_random_uuids=*/true);

  const CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);

  test::SaveCreativeNewTabPageAds({creative_ad_1, creative_ad_2});

  // Act & Assert
  base::test::TestFuture<bool, std::string, CreativeNewTabPageAdInfo>
      test_future;
  database_table_.GetForCreativeInstanceId(
      creative_ad_1.creative_instance_id,
      test_future.GetCallback<bool, const std::string&,
                              const CreativeNewTabPageAdInfo&>());
  const auto [success, creative_instance_id, creative_ad] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ(creative_ad_1.creative_instance_id, creative_instance_id);
  EXPECT_EQ(creative_ad_1, creative_ad);
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest,
       DoNotGetForCreativeInstanceIdIfTypeIsRichMediaAndJavascriptIsDisabled) {
  // Arrange
  test::SetUpAllowJavaScript(false);

  const CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(
          CreativeNewTabPageAdWallpaperType::kRichMedia,
          /*use_random_uuids=*/true);

  const CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);

  test::SaveCreativeNewTabPageAds({creative_ad_1, creative_ad_2});

  // Act & Assert
  base::test::TestFuture<bool, std::string, CreativeNewTabPageAdInfo>
      test_future;
  database_table_.GetForCreativeInstanceId(
      creative_ad_1.creative_instance_id,
      test_future.GetCallback<bool, const std::string&,
                              const CreativeNewTabPageAdInfo&>());
  const auto [success, creative_instance_id, creative_ad] = test_future.Take();
  EXPECT_FALSE(success);
  EXPECT_EQ(creative_ad_1.creative_instance_id, creative_instance_id);
  EXPECT_EQ(CreativeNewTabPageAdInfo{}, creative_ad);
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest,
       DoNotGetForMissingCreativeInstanceId) {
  // Arrange
  const CreativeNewTabPageAdList saved_creative_ads =
      test::BuildCreativeNewTabPageAds(
          CreativeNewTabPageAdWallpaperType::kImage, /*count=*/1);
  test::SaveCreativeNewTabPageAds(saved_creative_ads);

  // Act & Assert
  base::test::TestFuture<bool, std::string, CreativeNewTabPageAdInfo>
      test_future;
  database_table_.GetForCreativeInstanceId(
      test::kMissingCreativeInstanceId,
      test_future.GetCallback<bool, const std::string&,
                              const CreativeNewTabPageAdInfo&>());
  const auto [success, creative_instance_id, creative_ad] = test_future.Take();
  EXPECT_FALSE(success);
  EXPECT_EQ(test::kMissingCreativeInstanceId, creative_instance_id);
  EXPECT_EQ(CreativeNewTabPageAdInfo{}, creative_ad);
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest,
       GetNonExpiredIfTypeIsImage) {
  // Arrange
  CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);
  creative_ad_1.start_at = test::DistantPast();
  creative_ad_1.end_at = test::Now();

  CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);
  creative_ad_2.start_at = test::DistantPast();
  creative_ad_2.end_at = test::DistantFuture();

  test::SaveCreativeNewTabPageAds({creative_ad_1, creative_ad_2});

  AdvanceClockBy(base::Milliseconds(1));

  // Act & Assert
  base::test::TestFuture<bool, SegmentList, CreativeNewTabPageAdList>
      test_future;
  database_table_.GetForActiveCampaigns(
      test_future
          .GetCallback<bool, const SegmentList&, CreativeNewTabPageAdList>());
  const auto [success, segments, creative_ads] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ(SegmentList{creative_ad_2.segment}, segments);
  EXPECT_THAT(creative_ads, ::testing::ElementsAre(creative_ad_2));
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest,
       GetNonExpiredIfTypeIsRichMedia) {
  // Arrange
  CreativeNewTabPageAdInfo creative_ad_1 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*use_random_uuids=*/true);
  creative_ad_1.start_at = test::DistantPast();
  creative_ad_1.end_at = test::Now();

  CreativeNewTabPageAdInfo creative_ad_2 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*use_random_uuids=*/true);
  creative_ad_2.start_at = test::DistantPast();
  creative_ad_2.end_at = test::DistantFuture();

  test::SaveCreativeNewTabPageAds({creative_ad_1, creative_ad_2});

  AdvanceClockBy(base::Milliseconds(1));

  // Act & Assert
  base::test::TestFuture<bool, SegmentList, CreativeNewTabPageAdList>
      test_future;
  database_table_.GetForActiveCampaigns(
      test_future
          .GetCallback<bool, const SegmentList&, CreativeNewTabPageAdList>());
  const auto [success, segments, creative_ads] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_EQ(SegmentList{creative_ad_2.segment}, segments);
  EXPECT_THAT(creative_ads, ::testing::ElementsAre(creative_ad_2));
}

TEST_F(CatsxpAdsCreativeNewTabPageAdsDatabaseTableTest,
       DoNotGetNonExpiredIfTypeIsRichMediaAndJavascriptIsDisabled) {
  // Arrange
  test::SetUpAllowJavaScript(false);

  CreativeNewTabPageAdInfo creative_ad_1 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*use_random_uuids=*/true);
  creative_ad_1.start_at = test::DistantPast();
  creative_ad_1.end_at = test::Now();

  CreativeNewTabPageAdInfo creative_ad_2 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*use_random_uuids=*/true);
  creative_ad_2.start_at = test::DistantPast();
  creative_ad_2.end_at = test::DistantFuture();

  test::SaveCreativeNewTabPageAds({creative_ad_1, creative_ad_2});

  AdvanceClockBy(base::Milliseconds(1));

  // Act & Assert
  base::test::TestFuture<bool, SegmentList, CreativeNewTabPageAdList>
      test_future;
  database_table_.GetForActiveCampaigns(
      test_future
          .GetCallback<bool, const SegmentList&, CreativeNewTabPageAdList>());
  const auto [success, segments, creative_ads] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(segments, ::testing::IsEmpty());
  EXPECT_THAT(creative_ads, ::testing::IsEmpty());
}

}  // namespace catsxp_ads
