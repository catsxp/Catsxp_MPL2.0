/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/interest/interest_segments.h"

#include <memory>

#include "base/test/mock_callback.h"
#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/resources/test/language_components_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/interest/interest_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/text_classification_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/test/targeting_test_helper.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsInterestSegmentsTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    targeting_helper_ = std::make_unique<test::TargetingHelper>();

    ads_client_notifier_.NotifyResourceComponentDidChange(
        test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  }

  std::unique_ptr<test::TargetingHelper> targeting_helper_;
};

TEST_F(CatsxpAdsInterestSegmentsTest, BuildInterestSegments) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kTextClassificationFeature);

  targeting_helper_->SimulateInterest();

  // Act & Assert
  base::MockCallback<BuildSegmentsCallback> callback;
  EXPECT_CALL(callback,
              Run(test::TargetingHelper::InterestExpectation().segments));
  BuildInterestSegments(callback.Get());
}

TEST_F(CatsxpAdsInterestSegmentsTest, BuildInterestSegmentsIfNoTargeting) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kTextClassificationFeature);

  // Act & Assert
  base::MockCallback<BuildSegmentsCallback> callback;
  EXPECT_CALL(callback, Run(/*segments=*/::testing::IsEmpty()));
  BuildInterestSegments(callback.Get());
}

TEST_F(CatsxpAdsInterestSegmentsTest,
       DoNotBuildInterestSegmentsIfFeatureIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndDisableFeature(kTextClassificationFeature);

  targeting_helper_->SimulateInterest();

  // Act & Assert
  base::MockCallback<BuildSegmentsCallback> callback;
  EXPECT_CALL(callback, Run(/*segments=*/::testing::IsEmpty()));
  BuildInterestSegments(callback.Get());
}

}  // namespace catsxp_ads
