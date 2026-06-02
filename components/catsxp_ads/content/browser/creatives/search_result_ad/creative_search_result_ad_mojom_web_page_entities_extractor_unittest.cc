/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/creative_search_result_ad_mojom_web_page_entities_extractor.h"

#include <array>

#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/creative_search_result_ad_constants.h"
#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/creative_search_result_ad_test_constants.h"
#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/test/creative_search_result_ad_mojom_test_util.h"
#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/test/creative_search_result_ad_mojom_web_page_entities_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "components/schema_org/common/metadata.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

void VerifyRequiredMojomCreativeAdExpectations(
    const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad) {
  EXPECT_THAT(
      *mojom_creative_ad,
      ::testing::FieldsAre(
          mojom::AdType::kSearchResultAd, test::kCreativeAdPlacementId,
          test::kCreativeAdCreativeInstanceId, test::kCreativeAdCreativeSetId,
          test::kCreativeAdCampaignId, test::kCreativeAdAdvertiserId,
          GURL(test::kCreativeAdLandingPage), test::kCreativeAdHeadlineText,
          test::kCreativeAdDescription,
          ::testing::DoubleEq(test::kCreativeAdRewardsValue),
          /*creative_set_conversion=*/::testing::_));
}

void VerifyRequiredMojomCreativeSetConversionExpectations(
    const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad) {
  EXPECT_THAT(
      mojom_creative_ad->creative_set_conversion->url_pattern,
      ::testing::Optional(std::string(test::kCreativeSetConversionUrlPattern)));
  EXPECT_EQ(mojom_creative_ad->creative_set_conversion->observation_window,
            test::kCreativeSetConversionObservationWindow);
}

}  // namespace

TEST(CatsxpAdsCreativeSearchResultAdMojomWebPageEntitiesExtractorTest, Extract) {
  const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
      test::CreativeSearchResultAdMojomWebPageEntities(
          /*excluded_property_names=*/{});

  const std::vector<mojom::CreativeSearchResultAdInfoPtr>
      creative_search_result_ads =
          ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
              mojom_web_page_entities);
  ASSERT_THAT(creative_search_result_ads, ::testing::SizeIs(1));
  const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad =
      creative_search_result_ads[0];
  ASSERT_TRUE(mojom_creative_ad);
  ASSERT_TRUE(mojom_creative_ad->creative_set_conversion);
  EXPECT_EQ(test::kCreativeAdPlacementId, mojom_creative_ad->placement_id);

  VerifyRequiredMojomCreativeAdExpectations(mojom_creative_ad);
  VerifyRequiredMojomCreativeSetConversionExpectations(mojom_creative_ad);
}

TEST(CatsxpAdsCreativeSearchResultAdMojomWebPageEntitiesExtractorTest,
     DoNotExtractIfEntityTypeIsUnsupported) {
  // Invalid type.
  const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
      test::CreativeSearchResultAdMojomWebPageEntities(
          /*excluded_property_names=*/{});

  const auto& mojom_property = mojom_web_page_entities[0]->properties[0];
  const auto& mojom_entity = mojom_property->values->get_entity_values()[0];
  mojom_entity->type = "unsupported";

  const std::vector<mojom::CreativeSearchResultAdInfoPtr>
      creative_search_result_ads =
          ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
              mojom_web_page_entities);
  EXPECT_THAT(creative_search_result_ads, ::testing::IsEmpty());
}

TEST(CatsxpAdsCreativeSearchResultAdMojomWebPageEntitiesExtractorTest,
     DoNotExtractForEmptyMojomWebPageEntities) {
  {
    const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities;

    const std::vector<mojom::CreativeSearchResultAdInfoPtr>
        creative_search_result_ads =
            ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                mojom_web_page_entities);
    EXPECT_THAT(creative_search_result_ads, ::testing::IsEmpty());
  }

  {
    const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
        test::CreativeSearchResultAdMojomWebPageEntities(
            /*excluded_property_names=*/{});
    mojom_web_page_entities[0]->type = "unsupported";

    const std::vector<mojom::CreativeSearchResultAdInfoPtr>
        creative_search_result_ads =
            ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                mojom_web_page_entities);
    EXPECT_THAT(creative_search_result_ads, ::testing::IsEmpty());
  }

  {
    const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
        test::CreativeSearchResultAdMojomWebPageEntities(
            /*excluded_property_names=*/{});
    mojom_web_page_entities[0]->properties.clear();

    const std::vector<mojom::CreativeSearchResultAdInfoPtr>
        creative_search_result_ads =
            ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                mojom_web_page_entities);
    EXPECT_THAT(creative_search_result_ads, ::testing::IsEmpty());
  }

  {
    const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
        test::CreativeSearchResultAdMojomWebPageEntities(
            /*excluded_property_names=*/{});
    const auto& mojom_property = mojom_web_page_entities[0]->properties[0];
    mojom_property->name = "unsupported";

    const std::vector<mojom::CreativeSearchResultAdInfoPtr>
        creative_search_result_ads =
            ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                mojom_web_page_entities);
    EXPECT_THAT(creative_search_result_ads, ::testing::IsEmpty());
  }

  {
    const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
        test::CreativeSearchResultAdMojomWebPageEntities(
            /*excluded_property_names=*/{});
    const auto& mojom_property = mojom_web_page_entities[0]->properties[0];
    mojom_property->values = schema_org::mojom::Values::NewEntityValues({});

    const std::vector<mojom::CreativeSearchResultAdInfoPtr>
        creative_search_result_ads =
            ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                mojom_web_page_entities);
    EXPECT_THAT(creative_search_result_ads, ::testing::IsEmpty());
  }

  {
    const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
        test::CreativeSearchResultAdMojomWebPageEntities(
            /*excluded_property_names=*/{});
    const auto& mojom_property = mojom_web_page_entities[0]->properties[0];
    mojom_property->values =
        schema_org::mojom::Values::NewStringValues({"unsupported"});

    const std::vector<mojom::CreativeSearchResultAdInfoPtr>
        creative_search_result_ads =
            ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                mojom_web_page_entities);
    EXPECT_THAT(creative_search_result_ads, ::testing::IsEmpty());
  }
}

TEST(CatsxpAdsCreativeSearchResultAdMojomWebPageEntitiesExtractorTest,
     DoNotExtractForMissingPlacementId) {
  const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
      test::CreativeSearchResultAdMojomWebPageEntities(
          /*excluded_property_names=*/{"data-placement-id"});

  const std::vector<mojom::CreativeSearchResultAdInfoPtr>
      creative_search_result_ads =
          ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
              mojom_web_page_entities);
  EXPECT_THAT(creative_search_result_ads, ::testing::IsEmpty());
}

TEST(CatsxpAdsCreativeSearchResultAdMojomWebPageEntitiesExtractorTest,
     ExtractWhenDataPlacementIdIncludeUnreservedCharacters) {
  const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
      test::CreativeSearchResultAdMojomWebPageEntitiesWithProperty(
          kCreativeAdPlacementIdPropertyName,
          test::kCreativeAdPlacementIdWithUnreservedCharacters);

  const std::vector<mojom::CreativeSearchResultAdInfoPtr>
      creative_search_result_ads =
          ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
              mojom_web_page_entities);
  ASSERT_THAT(creative_search_result_ads, ::testing::SizeIs(1));
  const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad =
      creative_search_result_ads[0];
  ASSERT_TRUE(mojom_creative_ad);
  EXPECT_EQ(test::kEscapedCreativeAdPlacementIdWithUnreservedCharacters,
            mojom_creative_ad->placement_id);
}

TEST(CatsxpAdsCreativeSearchResultAdMojomWebPageEntitiesExtractorTest,
     ExtractWhenIncludesUnknownProperties) {
  const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
      test::CreativeSearchResultAdMojomWebPageEntitiesWithProperty(
          /*name=*/"foo",
          /*value=*/"bar");

  const std::vector<mojom::CreativeSearchResultAdInfoPtr>
      creative_search_result_ads =
          ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
              mojom_web_page_entities);
  ASSERT_THAT(creative_search_result_ads, ::testing::SizeIs(1));

  const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad =
      creative_search_result_ads[0];
  ASSERT_TRUE(mojom_creative_ad);
  ASSERT_TRUE(mojom_creative_ad->creative_set_conversion);
  EXPECT_EQ(test::kCreativeAdPlacementId, mojom_creative_ad->placement_id);

  VerifyRequiredMojomCreativeAdExpectations(mojom_creative_ad);
  VerifyRequiredMojomCreativeSetConversionExpectations(mojom_creative_ad);
}

TEST(CatsxpAdsCreativeSearchResultAdMojomWebPageEntitiesExtractorTest,
     DoNotExtractIfMissingRequiredCreativeAdProperties) {
  static constexpr auto kRequiredCreativeAdPropertyNames =
      std::to_array<std::string_view>(
          {kCreativeAdPlacementIdPropertyName,
           kCreativeAdCreativeInstanceIdPropertyName,
           kCreativeAdCreativeSetIdPropertyName,
           kCreativeAdCampaignIdPropertyName,
           kCreativeAdAdvertiserIdPropertyName,
           kCreativeAdHeadlineTextPropertyName,
           kCreativeAdDescriptionPropertyName,
           kCreativeAdLandingPagePropertyName,
           kCreativeAdRewardsValuePropertyName});

  for (auto property_name : kRequiredCreativeAdPropertyNames) {
    const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
        test::CreativeSearchResultAdMojomWebPageEntities(
            /*excluded_property_names=*/{property_name});

    const std::vector<mojom::CreativeSearchResultAdInfoPtr>
        creative_search_result_ads =
            ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                mojom_web_page_entities);
    EXPECT_THAT(creative_search_result_ads, ::testing::IsEmpty());
  }
}

TEST(CatsxpAdsCreativeSearchResultAdMojomWebPageEntitiesExtractorTest,
     DoNotExtractInvalidCreativeAdProperties) {
  {
    // Invalid "data-landing-page".
    const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
        test::CreativeSearchResultAdMojomWebPageEntitiesWithProperty(
            kCreativeAdLandingPagePropertyName, /*value=*/"http://catsxp.com");

    const std::vector<mojom::CreativeSearchResultAdInfoPtr>
        creative_search_result_ads =
            ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                mojom_web_page_entities);
    EXPECT_THAT(creative_search_result_ads, ::testing::IsEmpty());
  }

  {
    // Invalid "data-rewards-value".
    const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
        test::CreativeSearchResultAdMojomWebPageEntitiesWithProperty(
            kCreativeAdRewardsValuePropertyName, /*value=*/"0-5");

    const std::vector<mojom::CreativeSearchResultAdInfoPtr>
        creative_search_result_ads =
            ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                mojom_web_page_entities);
    EXPECT_THAT(creative_search_result_ads, ::testing::IsEmpty());
  }

  {
    // Invalid "data-conversion-observation-window-value".
    const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
        test::CreativeSearchResultAdMojomWebPageEntitiesWithProperty(
            kCreativeSetConversionObservationWindowPropertyName, /*value=*/"1");

    const std::vector<mojom::CreativeSearchResultAdInfoPtr>
        creative_search_result_ads =
            ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                mojom_web_page_entities);
    EXPECT_THAT(creative_search_result_ads, ::testing::IsEmpty());
  }

  {
    // Invalid "data-creative-instance-id".
    const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
        test::CreativeSearchResultAdMojomWebPageEntities(
            /*excluded_property_names=*/{
                kCreativeAdCreativeInstanceIdPropertyName});
    const auto& mojom_property = mojom_web_page_entities[0]->properties[0];
    auto& mojom_entity = mojom_property->values->get_entity_values()[0];
    test::AddMojomProperty<int64_t>(&mojom_entity->properties,
                                    kCreativeAdCreativeInstanceIdPropertyName,
                                    /*value=*/101);

    const std::vector<mojom::CreativeSearchResultAdInfoPtr>
        creative_search_result_ads =
            ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                mojom_web_page_entities);
    EXPECT_THAT(creative_search_result_ads, ::testing::IsEmpty());
  }
}

TEST(CatsxpAdsCreativeSearchResultAdMojomWebPageEntitiesExtractorTest,
     ExtractWithEmptyConversionUrlPattern) {
  // Arrange
  const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
      test::CreativeSearchResultAdMojomWebPageEntitiesWithProperty(
          kCreativeSetConversionUrlPatternPropertyName, /*value=*/"");

  // Act
  const std::vector<mojom::CreativeSearchResultAdInfoPtr>
      creative_search_result_ads =
          ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
              mojom_web_page_entities);

  // Assert
  ASSERT_THAT(creative_search_result_ads, ::testing::SizeIs(1));
  const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad =
      creative_search_result_ads[0];
  ASSERT_TRUE(mojom_creative_ad);
  ASSERT_TRUE(mojom_creative_ad->creative_set_conversion);
  EXPECT_FALSE(mojom_creative_ad->creative_set_conversion->url_pattern);
}

TEST(CatsxpAdsCreativeSearchResultAdMojomWebPageEntitiesExtractorTest,
     DoNotExtractIfMissingRequiredCreativeSetConversionProperties) {
  static constexpr auto kRequiredCreativeSetConversionPropertyNames =
      std::to_array<std::string_view>(
          {kCreativeSetConversionUrlPatternPropertyName,
           kCreativeSetConversionObservationWindowPropertyName});

  for (auto property_name : kRequiredCreativeSetConversionPropertyNames) {
    const std::vector<schema_org::mojom::EntityPtr> mojom_web_page_entities =
        test::CreativeSearchResultAdMojomWebPageEntities(
            /*excluded_property_names=*/{property_name});

    const std::vector<mojom::CreativeSearchResultAdInfoPtr>
        creative_search_result_ads =
            ExtractCreativeSearchResultAdsFromMojomWebPageEntities(
                mojom_web_page_entities);
    ASSERT_THAT(creative_search_result_ads, ::testing::SizeIs(1));
    const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad =
        creative_search_result_ads[0];
    ASSERT_TRUE(mojom_creative_ad);
    EXPECT_EQ(test::kCreativeAdPlacementId, mojom_creative_ad->placement_id);

    VerifyRequiredMojomCreativeAdExpectations(mojom_creative_ad);
    EXPECT_FALSE(mojom_creative_ad->creative_set_conversion);
  }
}

}  // namespace catsxp_ads
