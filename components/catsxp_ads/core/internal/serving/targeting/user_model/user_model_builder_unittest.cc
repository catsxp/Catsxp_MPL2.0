/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/user_model_builder.h"

#include <memory>

#include "base/test/mock_callback.h"
#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/resources/test/country_components_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/resources/test/language_components_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/text_classification_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/test/targeting_test_helper.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsUserModelBuilderTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    scoped_feature_list_.InitWithFeatures(
        /*enabled_features=*/{kPurchaseIntentFeature,
                              kTextClassificationFeature},
        /*disabled_features=*/{});

    targeting_helper_ = std::make_unique<test::TargetingHelper>();

    ads_client_notifier_.NotifyResourceComponentDidChange(
        test::kCountryComponentManifestVersion, test::kCountryComponentId);

    ads_client_notifier_.NotifyResourceComponentDidChange(
        test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  }

  base::test::ScopedFeatureList scoped_feature_list_;

  std::unique_ptr<test::TargetingHelper> targeting_helper_;
};

TEST_F(CatsxpAdsUserModelBuilderTest, BuildUserModel) {
  // Arrange
  targeting_helper_->Simulate();

  // Act & Assert
  base::MockCallback<BuildUserModelCallback> callback;
  EXPECT_CALL(callback, Run(test::TargetingHelper::Expectation()));
  BuildUserModel(callback.Get());
}

TEST_F(CatsxpAdsUserModelBuilderTest, BuildUserModelIfNoTargeting) {
  // Act & Assert
  base::MockCallback<BuildUserModelCallback> callback;
  EXPECT_CALL(callback, Run(UserModelInfo{}));
  BuildUserModel(callback.Get());
}

}  // namespace catsxp_ads
