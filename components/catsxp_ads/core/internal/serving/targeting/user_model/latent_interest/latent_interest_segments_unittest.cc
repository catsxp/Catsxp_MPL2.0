/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/latent_interest/latent_interest_segments.h"

#include <memory>

#include "base/test/mock_callback.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/latent_interest/latent_interest_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/test/targeting_test_helper.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsLatentInterestSegmentsTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    targeting_helper_ = std::make_unique<test::TargetingHelper>();
  }

  std::unique_ptr<test::TargetingHelper> targeting_helper_;
};

TEST_F(CatsxpAdsLatentInterestSegmentsTest, BuildLatentInterestSegments) {
  // Arrange
  targeting_helper_->SimulateLatentInterest();

  // Act & Assert
  base::MockCallback<BuildSegmentsCallback> callback;
  EXPECT_CALL(callback,
              Run(test::TargetingHelper::LatentInterestExpectation().segments));
  BuildLatentInterestSegments(callback.Get());
}

TEST_F(CatsxpAdsLatentInterestSegmentsTest,
       BuildLatentInterestSegmentsIfNoTargeting) {
  // Act & Assert
  base::MockCallback<BuildSegmentsCallback> callback;
  EXPECT_CALL(callback, Run(/*segments=*/::testing::IsEmpty()));
  BuildLatentInterestSegments(callback.Get());
}

TEST_F(CatsxpAdsLatentInterestSegmentsTest,
       DoNotBuildLatentInterestSegmentsIfFeatureIsDisabled) {
  // Arrange
  targeting_helper_->SimulateLatentInterest();

  // Act & Assert
  base::MockCallback<BuildSegmentsCallback> callback;
  EXPECT_CALL(callback, Run(/*segments=*/::testing::IsEmpty()));
  BuildLatentInterestSegments(callback.Get());
}

}  // namespace catsxp_ads
