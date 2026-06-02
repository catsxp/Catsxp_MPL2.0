/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/browser/network/oblivious_http_feature.h"

#include "base/feature_list.h"
#include "base/time/time.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsObliviousHttpFeatureTest, IsDisabled) {
  EXPECT_FALSE(base::FeatureList::IsEnabled(kAdsObliviousHttpFeature));
}

TEST(CatsxpAdsObliviousHttpFeatureTest, ShouldNotSupport) {
  EXPECT_FALSE(kShouldSupportOhttp.Get());
}

TEST(CatsxpAdsObliviousHttpFeatureTest, TimeoutDuration) {
  EXPECT_EQ(base::Seconds(3), kOhttpTimeoutDuration.Get());
}

TEST(CatsxpAdsObliviousHttpFeatureTest, KeyConfigExpiresAfter) {
  EXPECT_EQ(base::Days(3), kOhttpKeyConfigExpiresAfter.Get());
}

TEST(CatsxpAdsObliviousHttpFeatureTest, InitialKeyConfigBackoffDelay) {
  EXPECT_EQ(base::Minutes(5), kOhttpKeyConfigInitialBackoffDelay.Get());
}

TEST(CatsxpAdsObliviousHttpFeatureTest, MaxKeyConfigBackoffDelay) {
  EXPECT_EQ(base::Days(1), kOhttpKeyConfigMaxBackoffDelay.Get());
}

}  // namespace catsxp_ads
