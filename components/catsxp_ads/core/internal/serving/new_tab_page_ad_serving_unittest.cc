/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/new_tab_page_ad_serving.h"

#include <utility>

#include "base/run_loop.h"
#include "base/test/gmock_callback_support.h"
#include "base/test/mock_callback.h"
#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/new_tab_page_ad_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/test/creative_new_tab_page_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/new_tab_page_ad_serving_delegate.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/new_tab_page_ad_serving_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/test/permission_rules_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/test/new_tab_page_ad_serving_delegate_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/anti_targeting/resource/anti_targeting_resource.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/geographical/subdivision/subdivision_targeting.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsNewTabPageAdServingTest : public test::TestBase {
 protected:
  void MaybeServeAd(MaybeServeNewTabPageAdCallback callback) {
    SubdivisionTargeting subdivision_targeting;
    AntiTargetingResource anti_targeting_resource;
    ad_serving_ = std::make_unique<NewTabPageAdServing>(
        subdivision_targeting, anti_targeting_resource);
    ad_serving_->SetDelegate(&delegate_mock_);

    ad_serving_->MaybeServeAd(std::move(callback));
  }

  ::testing::StrictMock<NewTabPageAdServingDelegateMock> delegate_mock_;
  std::unique_ptr<NewTabPageAdServing> ad_serving_;
};

TEST_F(CatsxpAdsNewTabPageAdServingTest, DoNotServeAdForUnsupportedVersion) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kNewTabPageAdServingFeature, {{"version", "0"}});

  test::ForcePermissionRules();

  const CreativeNewTabPageAdInfo creative_ad =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);
  test::SaveCreativeNewTabPageAds({creative_ad});

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnFailedToServeNewTabPageAd);

  base::MockCallback<MaybeServeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*ad=*/::testing::Eq(std::nullopt)))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  MaybeServeAd(callback.Get());
  run_loop.Run();
}

TEST_F(CatsxpAdsNewTabPageAdServingTest, ServeAd) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kNewTabPageAdServingFeature);

  test::ForcePermissionRules();

  const CreativeNewTabPageAdInfo creative_ad =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);
  test::SaveCreativeNewTabPageAds({creative_ad});
  const NewTabPageAdInfo ad = BuildNewTabPageAd(creative_ad);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnOpportunityAroseToServeNewTabPageAd);

  EXPECT_CALL(delegate_mock_, OnDidServeNewTabPageAd);

  base::MockCallback<MaybeServeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*ad=*/::testing::Ne(std::nullopt)))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  MaybeServeAd(callback.Get());
  run_loop.Run();
}

TEST_F(CatsxpAdsNewTabPageAdServingTest, DoNotServeAdIfNoEligibleAdsFound) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kNewTabPageAdServingFeature);

  test::ForcePermissionRules();

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnOpportunityAroseToServeNewTabPageAd);

  EXPECT_CALL(delegate_mock_, OnFailedToServeNewTabPageAd);

  base::MockCallback<MaybeServeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*ad=*/::testing::Eq(std::nullopt)))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  MaybeServeAd(callback.Get());
  run_loop.Run();
}

TEST_F(CatsxpAdsNewTabPageAdServingTest,
       DoNotServeAdIfNotAllowedDueToPermissionRules) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kNewTabPageAdServingFeature);

  const CreativeNewTabPageAdInfo creative_ad =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*use_random_uuids=*/true);
  test::SaveCreativeNewTabPageAds({creative_ad});

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnFailedToServeNewTabPageAd);

  base::MockCallback<MaybeServeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*ad=*/::testing::Eq(std::nullopt)))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  MaybeServeAd(callback.Get());
  run_loop.Run();
}

}  // namespace catsxp_ads
