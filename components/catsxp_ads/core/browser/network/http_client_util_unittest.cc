/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/browser/network/http_client_util.h"

#include "net/traffic_annotation/network_traffic_annotation.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsHttpclientUtilTest, ObliviousHttpKeyConfigUrl) {
  EXPECT_EQ(GURL("https://static.ads.catsxpsoftware.com/v1/ohttp/hpkekeyconfig"),
            ObliviousHttpKeyConfigUrl(/*use_staging=*/true));
  EXPECT_EQ(GURL("https://static.ads.catsxp.com/v1/ohttp/hpkekeyconfig"),
            ObliviousHttpKeyConfigUrl(/*use_staging=*/false));
}

TEST(CatsxpAdsHttpclientUtilTest, ObliviousHttpRelayUrl) {
  EXPECT_EQ(GURL("https://ohttp.ads.catsxpsoftware.com/v1/ohttp/gateway"),
            ObliviousHttpRelayUrl(/*use_staging=*/true));
  EXPECT_EQ(GURL("https://ohttp.ads.catsxp.com/v1/ohttp/gateway"),
            ObliviousHttpRelayUrl(/*use_staging=*/false));
}

TEST(CatsxpAdsHttpclientUtilTest, GetNetworkTrafficAnnotationTag) {
  EXPECT_EQ(18366277, GetNetworkTrafficAnnotationTag().unique_id_hash_code);
}

}  // namespace catsxp_ads
