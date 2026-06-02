/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_model.h"

#include <memory>

#include "base/test/run_until.h"
#include "catsxp/components/catsxp_ads/core/internal/common/resources/test/country_components_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_processor.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_resource.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsPurchaseIntentModelTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    resource_ = std::make_unique<PurchaseIntentResource>();
  }

  std::unique_ptr<PurchaseIntentResource> resource_;
};

TEST_F(CatsxpAdsPurchaseIntentModelTest,
       DoNotGetSegmentsForUnitializedResource) {
  // Arrange
  PurchaseIntentProcessor processor(*resource_);
  processor.Process(GURL("https://www.catsxp.com/test?foo=bar"));

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  EXPECT_THAT(purchase_intent_segments, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsPurchaseIntentModelTest, DoNotGetSegmentsForExpiredSignals) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  PurchaseIntentProcessor processor(*resource_);
  processor.Process(GURL("https://www.catsxp.com/test?foo=bar"));

  AdvanceClockBy(base::Days(1));

  processor.Process(GURL("https://www.basicattentiontoken.org/test?bar=foo"));

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  EXPECT_THAT(purchase_intent_segments, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsPurchaseIntentModelTest, DoNotGetSegmentsIfNeverProcessed) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  EXPECT_THAT(purchase_intent_segments, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsPurchaseIntentModelTest,
       DoNotGetSegmentsIfNeverMatchedFunnelSites) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  PurchaseIntentProcessor processor(*resource_);
  processor.Process(GURL("https://duckduckgo.com/?q=segment+keyword+1"));

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  EXPECT_THAT(purchase_intent_segments, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsPurchaseIntentModelTest, GetSegmentsForPreviouslyMatchedSite) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  PurchaseIntentProcessor processor(*resource_);
  processor.Process(GURL("https://www.catsxp.com/test?foo=bar"));
  processor.Process(GURL("https://basicattentiontoken.org/test?bar=foo"));
  processor.Process(GURL("https://www.catsxp.com/test?foo=bar"));

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  const SegmentList expected_purchase_intent_segments = {"segment 3",
                                                         "segment 2"};
  EXPECT_EQ(expected_purchase_intent_segments, purchase_intent_segments);
}

TEST_F(CatsxpAdsPurchaseIntentModelTest,
       GetSegmentsForPreviouslyMatchedSegmentKeyphrases) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  const GURL url = GURL("https://duckduckgo.com/?q=segment+keyword+1&foo=bar");

  PurchaseIntentProcessor processor(*resource_);
  processor.Process(url);
  processor.Process(url);
  processor.Process(url);

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  const SegmentList expected_purchase_intent_segments = {"segment 1"};
  EXPECT_EQ(expected_purchase_intent_segments, purchase_intent_segments);
}

TEST_F(CatsxpAdsPurchaseIntentModelTest,
       GetSegmentsForPreviouslyMatchedFunnelKeywords) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  PurchaseIntentProcessor processor(*resource_);
  processor.Process(
      GURL("https://duckduckgo.com/?q=segment+keyword+1+funnel+keyword+2"));

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  const SegmentList expected_purchase_intent_segments = {"segment 1"};
  EXPECT_EQ(expected_purchase_intent_segments, purchase_intent_segments);
}

}  // namespace catsxp_ads
