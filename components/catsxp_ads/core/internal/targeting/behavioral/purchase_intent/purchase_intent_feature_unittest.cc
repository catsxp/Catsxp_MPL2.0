/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_feature.h"

#include "base/time/time.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsPurchaseIntentFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kPurchaseIntentFeature));
}

TEST(CatsxpAdsPurchaseIntentFeatureTest, PurchaseIntentResourceVersion) {
  // Act & Assert
  EXPECT_EQ(1, kPurchaseIntentResourceVersion.Get());
}

TEST(CatsxpAdsPurchaseIntentFeatureTest, PurchaseIntentThreshold) {
  // Act & Assert
  EXPECT_EQ(3, kPurchaseIntentThreshold.Get());
}

TEST(CatsxpAdsPurchaseIntentFeatureTest, PurchaseIntentTimeWindow) {
  // Act & Assert
  EXPECT_EQ(base::Days(7), kPurchaseIntentTimeWindow.Get());
}

}  // namespace catsxp_ads
