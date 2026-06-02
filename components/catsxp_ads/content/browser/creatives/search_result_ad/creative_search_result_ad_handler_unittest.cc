/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/creative_search_result_ad_handler.h"

#include <memory>
#include <string_view>
#include <utility>

#include "base/check.h"
#include "base/test/mock_callback.h"
#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/creative_search_result_ad_constants.h"
#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/creative_search_result_ad_mojom_web_page_entities_extractor.h"
#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/creative_search_result_ad_test_constants.h"
#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/test/creative_search_result_ad_mojom_web_page_entities_test_util.h"
#include "catsxp/components/catsxp_ads/core/browser/service/test/ads_service_mock.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/blink/public/mojom/document_metadata/document_metadata.mojom.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

constexpr std::string_view kAllowedDomain = "https://search.catsxp.com";
constexpr std::string_view kDisallowedDomain = "https://catsxp.com";

}  // namespace

class CatsxpAdsCreativeSearchResultAdHandlerTest : public ::testing::Test {
 public:
  static void SimulateMaybeExtractCreativeAdPlacementIdsFromWebPageCallback(
      CreativeSearchResultAdHandler* creative_search_result_ad_handler,
      blink::mojom::WebPagePtr mojom_web_page) {
    CHECK(creative_search_result_ad_handler);

    base::MockCallback<ExtractCreativeAdPlacementIdsFromWebPageCallback>
        callback;
    EXPECT_CALL(callback, Run)
        .WillOnce([creative_search_result_ad_handler](
                      std::vector<mojom::CreativeSearchResultAdInfoPtr>
                          creative_search_result_ads) {
          for (auto& creative_search_result_ad : creative_search_result_ads) {
            creative_search_result_ad_handler
                ->MaybeTriggerCreativeAdViewedEvent(
                    std::move(creative_search_result_ad));
          }
        });

    creative_search_result_ad_handler
        ->MaybeExtractCreativeAdPlacementIdsFromWebPageCallback(
            mojo::Remote<blink::mojom::DocumentMetadata>(), callback.Get(),
            std::move(mojom_web_page));
  }

 protected:
  AdsServiceMock ads_service_mock_;
};

TEST_F(CatsxpAdsCreativeSearchResultAdHandlerTest, Create) {
  // Act
  const auto creative_search_result_ad_handler =
      CreativeSearchResultAdHandler::MaybeCreate(
          &ads_service_mock_, GURL(kAllowedDomain),
          /*should_trigger_creative_ad_viewed_events=*/true);

  // Assert
  EXPECT_TRUE(creative_search_result_ad_handler);
}

TEST_F(CatsxpAdsCreativeSearchResultAdHandlerTest,
       DoNotCreateWhenAdsServiceIsNull) {
  // Act
  const auto creative_search_result_ad_handler =
      CreativeSearchResultAdHandler::MaybeCreate(
          /*ads_service=*/nullptr, GURL(kAllowedDomain),
          /*should_trigger_creative_ad_viewed_events=*/true);

  // Assert
  EXPECT_FALSE(creative_search_result_ad_handler);
}

TEST_F(CatsxpAdsCreativeSearchResultAdHandlerTest,
       DoNotCreateForDisallowedDomain) {
  // Act
  const auto creative_search_result_ad_handler =
      CreativeSearchResultAdHandler::MaybeCreate(
          &ads_service_mock_, GURL(kDisallowedDomain),
          /*should_trigger_creative_ad_viewed_events=*/true);

  // Assert
  EXPECT_FALSE(creative_search_result_ad_handler);
}

TEST_F(CatsxpAdsCreativeSearchResultAdHandlerTest,
       ShouldNotTriggerAdViewedEvents) {
  // Arrange
  const auto creative_search_result_ad_handler =
      CreativeSearchResultAdHandler::MaybeCreate(
          &ads_service_mock_, GURL(kAllowedDomain),
          /*should_trigger_creative_ad_viewed_events=*/false);
  ASSERT_TRUE(creative_search_result_ad_handler);

  blink::mojom::WebPagePtr mojom_web_page =
      test::CreativeSearchResultAdMojomWebPage(/*excluded_property_names=*/{});
  ASSERT_TRUE(mojom_web_page);

  // Act & Assert
  EXPECT_CALL(ads_service_mock_,
              TriggerSearchResultAdEvent(
                  /*mojom_creative_ad=*/::testing::_,
                  mojom::SearchResultAdEventType::kViewedImpression,
                  /*callback=*/::testing::_))
      .Times(0);

  SimulateMaybeExtractCreativeAdPlacementIdsFromWebPageCallback(
      creative_search_result_ad_handler.get(), std::move(mojom_web_page));
}

TEST_F(CatsxpAdsCreativeSearchResultAdHandlerTest,
       DoNotTriggerViewedAdEventForInvalidWebPage) {
  // Arrange
  const auto creative_search_result_ad_handler =
      CreativeSearchResultAdHandler::MaybeCreate(
          &ads_service_mock_, GURL(kAllowedDomain),
          /*should_trigger_creative_ad_viewed_events=*/true);
  ASSERT_TRUE(creative_search_result_ad_handler);

  // Act & Assert
  EXPECT_CALL(ads_service_mock_,
              TriggerSearchResultAdEvent(
                  /*mojom_creative_ad=*/::testing::_,
                  mojom::SearchResultAdEventType::kViewedImpression,
                  /*callback=*/::testing::_))
      .Times(0);

  SimulateMaybeExtractCreativeAdPlacementIdsFromWebPageCallback(
      creative_search_result_ad_handler.get(), blink::mojom::WebPagePtr());
}

TEST_F(CatsxpAdsCreativeSearchResultAdHandlerTest,
       DoNotTriggerViewedAdEventForEmptyWebPage) {
  // Arrange
  const auto creative_search_result_ad_handler =
      CreativeSearchResultAdHandler::MaybeCreate(
          &ads_service_mock_, GURL(kAllowedDomain),
          /*should_trigger_creative_ad_viewed_events=*/true);
  ASSERT_TRUE(creative_search_result_ad_handler);

  // Act & Assert
  EXPECT_CALL(ads_service_mock_,
              TriggerSearchResultAdEvent(
                  /*mojom_creative_ad=*/::testing::_,
                  mojom::SearchResultAdEventType::kViewedImpression,
                  /*callback=*/::testing::_))
      .Times(0);

  SimulateMaybeExtractCreativeAdPlacementIdsFromWebPageCallback(
      creative_search_result_ad_handler.get(), blink::mojom::WebPage::New());
}

TEST_F(CatsxpAdsCreativeSearchResultAdHandlerTest,
       DoNotTriggerViewedAdEventForInvalidCreativeAd) {
  // Arrange
  const auto creative_search_result_ad_handler =
      CreativeSearchResultAdHandler::MaybeCreate(
          &ads_service_mock_, GURL(kAllowedDomain),
          /*should_trigger_creative_ad_viewed_events=*/true);
  ASSERT_TRUE(creative_search_result_ad_handler);

  // Act & Assert
  EXPECT_CALL(ads_service_mock_,
              TriggerSearchResultAdEvent(
                  /*mojom_creative_ad=*/::testing::_,
                  mojom::SearchResultAdEventType::kViewedImpression,
                  /*callback=*/::testing::_))
      .Times(0);

  SimulateMaybeExtractCreativeAdPlacementIdsFromWebPageCallback(
      creative_search_result_ad_handler.get(),
      test::CreativeSearchResultAdMojomWebPage(
          /*excluded_property_names=*/{kCreativeAdRewardsValuePropertyName}));
}

TEST_F(CatsxpAdsCreativeSearchResultAdHandlerTest,
       DoNotTriggerViewedAdEventForInvalidCreativeSetConversion) {
  // Arrange
  const auto creative_search_result_ad_handler =
      CreativeSearchResultAdHandler::MaybeCreate(
          &ads_service_mock_, GURL(kAllowedDomain),
          /*should_trigger_creative_ad_viewed_events=*/true);
  ASSERT_TRUE(creative_search_result_ad_handler);

  // Act & Assert
  EXPECT_CALL(ads_service_mock_,
              TriggerSearchResultAdEvent(
                  /*mojom_creative_ad=*/::testing::_,
                  mojom::SearchResultAdEventType::kViewedImpression,
                  /*callback=*/::testing::_))
      .WillOnce([](mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad,
                   mojom::SearchResultAdEventType /*mojom_ad_event_type*/,
                   ResultCallback /*callback*/) {
        EXPECT_FALSE(mojom_creative_ad->creative_set_conversion);
      });

  SimulateMaybeExtractCreativeAdPlacementIdsFromWebPageCallback(
      creative_search_result_ad_handler.get(),
      test::CreativeSearchResultAdMojomWebPage(
          /*excluded_property_names=*/{
              kCreativeSetConversionUrlPatternPropertyName}));
}

TEST_F(CatsxpAdsCreativeSearchResultAdHandlerTest, TriggerAdViewedEvent) {
  // Arrange
  const auto creative_search_result_ad_handler =
      CreativeSearchResultAdHandler::MaybeCreate(
          &ads_service_mock_, GURL(kAllowedDomain),
          /*should_trigger_creative_ad_viewed_events=*/true);
  ASSERT_TRUE(creative_search_result_ad_handler);

  const blink::mojom::WebPagePtr mojom_web_page =
      test::CreativeSearchResultAdMojomWebPage(/*excluded_property_names=*/{});
  ASSERT_TRUE(mojom_web_page);

  // Act & Assert
  EXPECT_CALL(ads_service_mock_,
              TriggerSearchResultAdEvent(
                  /*mojom_creative_ad=*/::testing::_,
                  mojom::SearchResultAdEventType::kViewedImpression,
                  /*callback=*/::testing::_))
      .WillOnce([&mojom_web_page](
                    mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad,
                    mojom::SearchResultAdEventType /*mojom_ad_event_type*/,
                    ResultCallback /*callback*/) {
        const std::vector<mojom::CreativeSearchResultAdInfoPtr>
            creative_search_result_ads =
                ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                    mojom_web_page->entities);
        ASSERT_EQ(creative_search_result_ads.size(), 1U);
        ASSERT_EQ(creative_search_result_ads[0]->placement_id,
                  test::kCreativeAdPlacementId);

        EXPECT_EQ(creative_search_result_ads[0], mojom_creative_ad);
      });

  SimulateMaybeExtractCreativeAdPlacementIdsFromWebPageCallback(
      creative_search_result_ad_handler.get(), mojom_web_page->Clone());
}

TEST_F(CatsxpAdsCreativeSearchResultAdHandlerTest,
       TriggerViewedAdEventWithUnreservedCharactersInPlacementId) {
  // Arrange
  const auto creative_search_result_ad_handler =
      CreativeSearchResultAdHandler::MaybeCreate(
          &ads_service_mock_, GURL(kAllowedDomain),
          /*should_trigger_creative_ad_viewed_events=*/true);
  ASSERT_TRUE(creative_search_result_ad_handler);

  const blink::mojom::WebPagePtr mojom_web_page =
      test::CreativeSearchResultAdMojomWebPageWithProperty(
          /*name=*/"data-placement-id",
          /*value=*/test::kCreativeAdPlacementIdWithUnreservedCharacters);
  ASSERT_TRUE(mojom_web_page);

  // Act & Assert
  EXPECT_CALL(ads_service_mock_,
              TriggerSearchResultAdEvent(
                  /*mojom_creative_ad=*/::testing::_,
                  mojom::SearchResultAdEventType::kViewedImpression,
                  /*callback=*/::testing::_))
      .WillOnce([&mojom_web_page](
                    mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad,
                    mojom::SearchResultAdEventType /*mojom_ad_event_type*/,
                    ResultCallback /*callback*/) {
        const std::vector<mojom::CreativeSearchResultAdInfoPtr>
            creative_search_result_ads =
                ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                    mojom_web_page->entities);
        ASSERT_EQ(creative_search_result_ads.size(), 1U);
        ASSERT_EQ(creative_search_result_ads[0]->placement_id,
                  test::kEscapedCreativeAdPlacementIdWithUnreservedCharacters);

        EXPECT_EQ(creative_search_result_ads[0], mojom_creative_ad);
      });

  SimulateMaybeExtractCreativeAdPlacementIdsFromWebPageCallback(
      creative_search_result_ad_handler.get(), mojom_web_page->Clone());
}

}  // namespace catsxp_ads
