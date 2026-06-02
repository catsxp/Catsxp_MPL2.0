/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/creative_search_result_ad_url_placement_id_extractor.h"

#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/creative_search_result_ad_test_constants.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCreativeSearchResultAdUrlPlacementIdExtractorTest,
     ExtractCreativeAdPlacementIdFromUrls) {
  // Allowed domains.
  EXPECT_EQ(
      test::kCreativeAdPlacementId,
      MaybeExtractCreativeAdPlacementIdFromUrl(GURL(
          R"(https://search.catsxp.com/a/redirect?click_url=https://catsxp.com&placement_id=953f362e-98cd-4fa6-8403-e886185b88fc&creative_instance_id=xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx)")));

  EXPECT_EQ(
      test::kCreativeAdPlacementId,
      MaybeExtractCreativeAdPlacementIdFromUrl(GURL(
          R"(https://safesearch.catsxp.com/a/redirect?click_url=https://catsxp.com&placement_id=953f362e-98cd-4fa6-8403-e886185b88fc&creative_instance_id=xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx)")));

  EXPECT_EQ(
      test::kCreativeAdPlacementId,
      MaybeExtractCreativeAdPlacementIdFromUrl(GURL(
          R"(https://search.catsxp.software/a/redirect?click_url=https://catsxp.com&placement_id=953f362e-98cd-4fa6-8403-e886185b88fc&creative_instance_id=xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx)")));
}

TEST(CatsxpAdsCreativeSearchResultAdUrlPlacementIdExtractorTest,
     DoNotExtractCreativeAdPlacementIdFromUrls) {
  // Invalid URL.
  EXPECT_FALSE(MaybeExtractCreativeAdPlacementIdFromUrl(GURL()));

  // Non https://.
  EXPECT_FALSE(MaybeExtractCreativeAdPlacementIdFromUrl(
      GURL(R"(http://search.catsxp.software/a/redirect)")));

  // Disallowed domain.
  EXPECT_FALSE(MaybeExtractCreativeAdPlacementIdFromUrl(
      GURL(R"(https://catsxp.software/a/redirect)")));

  // Invalid path.
  EXPECT_FALSE(MaybeExtractCreativeAdPlacementIdFromUrl(
      GURL(R"(https://search.catsxp.software/foo/bar)")));

  // No query.
  EXPECT_FALSE(MaybeExtractCreativeAdPlacementIdFromUrl(
      GURL("https://search.catsxp.software/a/redirect?")));

  // No `placement_id` query.
  EXPECT_FALSE(MaybeExtractCreativeAdPlacementIdFromUrl(GURL(
      R"(https://search.catsxp.software/a/redirect?click_url=https://catsxp.com&creative_instance_id=xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx)")));

  // No `placement_id` query value.
  EXPECT_FALSE(MaybeExtractCreativeAdPlacementIdFromUrl(GURL(
      R"(https://search.catsxp.software/a/redirect?click_url=https://catsxp.com&placement_id=)")));

  EXPECT_FALSE(MaybeExtractCreativeAdPlacementIdFromUrl(GURL(
      R"(https://search.catsxp.software/a/redirect?click_url=https://catsxp.com&placement_id)")));
}

}  // namespace catsxp_ads
