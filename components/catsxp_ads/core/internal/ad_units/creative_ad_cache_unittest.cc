/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ad_units/creative_ad_cache.h"

#include <memory>

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/search_result_ads/test/creative_search_result_ad_test_util.h"
#include "net/http/http_status_code.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCreativeAdCacheTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    creative_ad_cache_ = std::make_unique<CreativeAdCache>();
  }

  std::unique_ptr<CreativeAdCache> creative_ad_cache_;
};

TEST_F(CatsxpAdsCreativeAdCacheTest, AddCreativeAd) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);

  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  // Act
  creative_ad_cache_->MaybeAdd(test::kPlacementId, mojom_creative_ad->Clone());

  // Assert
  EXPECT_EQ(mojom_creative_ad,
            creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
                test::kPlacementId));
}

TEST_F(CatsxpAdsCreativeAdCacheTest, DoNotAddCreativeAd) {
  // Arrange
  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  // Act
  creative_ad_cache_->MaybeAdd(test::kPlacementId,
                               mojom::CreativeSearchResultAdInfoPtr{});

  // Assert
  EXPECT_FALSE(
      creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
          test::kPlacementId));
}

TEST_F(CatsxpAdsCreativeAdCacheTest, DoNotAddInvalidCreativeAd) {
  // Arrange
  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);

  CreativeAdVariant creative_ad_variant;

  // Act
  creative_ad_cache_->MaybeAdd(test::kPlacementId,
                               std::move(creative_ad_variant));

  // Assert
  EXPECT_FALSE(
      creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
          test::kPlacementId));
}

TEST_F(CatsxpAdsCreativeAdCacheTest, DoNotAddCreativeAdForOccludedTab) {
  // Arrange
  CreativeAdVariant creative_ad_variant(
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true));

  // Act
  creative_ad_cache_->MaybeAdd(test::kPlacementId,
                               std::move(creative_ad_variant));

  // Assert
  EXPECT_FALSE(
      creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
          test::kPlacementId));
}

TEST_F(CatsxpAdsCreativeAdCacheTest, DoNotGetCreativeAdForMissingPlacementId) {
  // Arrange
  CreativeAdVariant creative_ad_variant(
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true));

  // Act
  creative_ad_cache_->MaybeAdd(test::kPlacementId,
                               std::move(creative_ad_variant));

  // Assert
  EXPECT_FALSE(
      creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
          test::kMissingPlacementId));
}

TEST_F(CatsxpAdsCreativeAdCacheTest, GetCreativeAdsAcrossMultipleTabs) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);

  // Act
  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);
  creative_ad_cache_->MaybeAdd(test::kPlacementId, mojom_creative_ad->Clone());

  tab_helper_.OpenTab(
      /*tab_id=*/2,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);
  creative_ad_cache_->MaybeAdd(test::kAnotherPlacementId,
                               mojom_creative_ad->Clone());

  // Assert
  EXPECT_EQ(mojom_creative_ad,
            creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
                test::kPlacementId));
  EXPECT_EQ(mojom_creative_ad,
            creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
                test::kAnotherPlacementId));
}

TEST_F(CatsxpAdsCreativeAdCacheTest, PurgePlacementsOnTabDidClose) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);

  tab_helper_.OpenTab(
      /*tab_id=*/1,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);
  creative_ad_cache_->MaybeAdd(test::kPlacementId, mojom_creative_ad->Clone());

  tab_helper_.OpenTab(
      /*tab_id=*/2,
      /*redirect_chain=*/{GURL("https://catsxp.com")}, net::HTTP_OK);
  creative_ad_cache_->MaybeAdd(test::kAnotherPlacementId,
                               mojom_creative_ad->Clone());

  // Act
  tab_helper_.CloseTab(/*tab_id=*/2);

  // Assert
  EXPECT_EQ(mojom_creative_ad,
            creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
                test::kPlacementId));
  EXPECT_FALSE(
      creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
          test::kAnotherPlacementId));
}

}  // namespace catsxp_ads
