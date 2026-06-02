/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/intent/intent_segments.h"

#include <memory>

#include "base/test/mock_callback.h"
#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/resources/test/country_components_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/intent/intent_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/test/targeting_test_helper.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsIntentSegmentsTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    targeting_helper_ = std::make_unique<test::TargetingHelper>();

    ads_client_notifier_.NotifyResourceComponentDidChange(
        test::kCountryComponentManifestVersion, test::kCountryComponentId);
  }

  std::unique_ptr<test::TargetingHelper> targeting_helper_;
};

TEST_F(CatsxpAdsIntentSegmentsTest, BuildIntentSegments) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPurchaseIntentFeature);

  targeting_helper_->SimulateIntent();

  // Act & Assert
  base::MockCallback<BuildSegmentsCallback> callback;
  EXPECT_CALL(callback,
              Run(test::TargetingHelper::IntentExpectation().segments));
  BuildIntentSegments(callback.Get());
}

TEST_F(CatsxpAdsIntentSegmentsTest, BuildIntentSegmentsIfNoTargeting) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPurchaseIntentFeature);

  // Act & Assert
  base::MockCallback<BuildSegmentsCallback> callback;
  EXPECT_CALL(callback, Run(/*segments=*/::testing::IsEmpty()));
  BuildIntentSegments(callback.Get());
}

TEST_F(CatsxpAdsIntentSegmentsTest,
       DoNotBuildIntentSegmentsIfFeatureIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndDisableFeature(kPurchaseIntentFeature);

  targeting_helper_->SimulateIntent();

  // Act & Assert
  base::MockCallback<BuildSegmentsCallback> callback;
  EXPECT_CALL(callback, Run(/*segments=*/::testing::IsEmpty()));
  BuildIntentSegments(callback.Get());
}

}  // namespace catsxp_ads
