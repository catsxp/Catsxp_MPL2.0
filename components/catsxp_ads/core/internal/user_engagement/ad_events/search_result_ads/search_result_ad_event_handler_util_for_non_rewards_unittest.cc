/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include <cstddef>

#include "base/test/test_future.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_database_table.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/search_result_ads/test/creative_search_result_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/search_result_ads/search_result_ad_event_handler_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSearchResultAdEventHandlerUtilForNonRewardsTest
    : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    test::DisableCatsxpRewards();
  }

  database::table::CreativeSetConversions
      creative_set_conversions_database_table_;
};

TEST_F(CatsxpAdsSearchResultAdEventHandlerUtilForNonRewardsTest,
       SaveCreativeSetConversionForClickedEventWithConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);

  // Act
  MaybeBuildAndSaveCreativeSetConversion(
      mojom_creative_ad, mojom::SearchResultAdEventType::kClicked);

  // Assert
  std::optional<CreativeSetConversionInfo> creative_set_conversion =
      FromMojomMaybeBuildCreativeSetConversion(mojom_creative_ad);
  ASSERT_TRUE(creative_set_conversion);

  base::test::TestFuture<bool, CreativeSetConversionList> test_future;
  creative_set_conversions_database_table_.GetUnexpired(
      test_future.GetCallback<bool, const CreativeSetConversionList&>());
  const auto [success, creative_set_conversions] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(creative_set_conversions,
              ::testing::ElementsAre(*creative_set_conversion));
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerUtilForNonRewardsTest,
       DoNotSaveCreativeSetConversionForNonClickedEventWithConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);

  // Act
  for (size_t i = 0;
       i < static_cast<size_t>(mojom::SearchResultAdEventType::kMaxValue);
       ++i) {
    const auto mojom_ad_event_type =
        static_cast<mojom::SearchResultAdEventType>(i);
    if (mojom_ad_event_type != mojom::SearchResultAdEventType::kClicked) {
      MaybeBuildAndSaveCreativeSetConversion(mojom_creative_ad,
                                             mojom_ad_event_type);
    }
  }

  // Assert
  base::test::TestFuture<bool, CreativeSetConversionList> test_future;
  creative_set_conversions_database_table_.GetUnexpired(
      test_future.GetCallback<bool, const CreativeSetConversionList&>());
  const auto [success, creative_set_conversions] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(creative_set_conversions, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerUtilForNonRewardsTest,
       DoNotSaveCreativeSetConversionForClickedEventWithoutConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAd(/*use_random_uuids=*/true);

  // Act
  MaybeBuildAndSaveCreativeSetConversion(
      mojom_creative_ad, mojom::SearchResultAdEventType::kClicked);

  // Assert
  base::test::TestFuture<bool, CreativeSetConversionList> test_future;
  creative_set_conversions_database_table_.GetUnexpired(
      test_future.GetCallback<bool, const CreativeSetConversionList&>());
  const auto [success, creative_set_conversions] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(creative_set_conversions, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerUtilForNonRewardsTest,
       NotAllowedToFireViewedEventWithConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_FALSE(IsAllowedToFireAdEvent(
      mojom_creative_ad, mojom::SearchResultAdEventType::kViewedImpression));
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerUtilForNonRewardsTest,
       NotAllowedToFireViewedEventWithoutConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAd(/*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_FALSE(IsAllowedToFireAdEvent(
      mojom_creative_ad, mojom::SearchResultAdEventType::kViewedImpression));
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerUtilForNonRewardsTest,
       NotAllowedToFireNonClickedEventWithConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);

  // Act & Assert
  for (size_t i = 0;
       i < static_cast<size_t>(mojom::SearchResultAdEventType::kMaxValue);
       ++i) {
    const auto mojom_ad_event_type =
        static_cast<mojom::SearchResultAdEventType>(i);
    if (mojom_ad_event_type != mojom::SearchResultAdEventType::kClicked) {
      EXPECT_FALSE(
          IsAllowedToFireAdEvent(mojom_creative_ad, mojom_ad_event_type));
    }
  }
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerUtilForNonRewardsTest,
       NotAllowedToFireClickedEventWithoutConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAd(/*use_random_uuids=*/true);

  // Act & Assert
  EXPECT_FALSE(IsAllowedToFireAdEvent(
      mojom_creative_ad, mojom::SearchResultAdEventType::kClicked));
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerUtilForNonRewardsTest,
       ShouldFireNonDuplicateClickedEvent) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);
  const SearchResultAdInfo ad = FromMojomBuildSearchResultAd(mojom_creative_ad);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_TRUE(ShouldFireAdEvent(ad, ad_events,
                                mojom::SearchResultAdEventType::kClicked));
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerUtilForNonRewardsTest,
       ShouldNotFireDuplicateClickedEvent) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);
  const SearchResultAdInfo ad = FromMojomBuildSearchResultAd(mojom_creative_ad);

  AdEventList ad_events;
  const AdEventInfo ad_event_1 =
      BuildAdEvent(ad, mojom::ConfirmationType::kServedImpression,
                   /*created_at=*/test::Now());
  ad_events.push_back(ad_event_1);
  const AdEventInfo ad_event_2 = BuildAdEvent(
      ad, mojom::ConfirmationType::kClicked, /*created_at=*/test::Now());
  ad_events.push_back(ad_event_2);

  // Act & Assert
  EXPECT_FALSE(ShouldFireAdEvent(ad, ad_events,
                                 mojom::SearchResultAdEventType::kClicked));
}

}  // namespace catsxp_ads
