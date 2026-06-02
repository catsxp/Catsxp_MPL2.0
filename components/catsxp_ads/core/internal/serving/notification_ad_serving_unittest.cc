/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/notification_ad_serving.h"

#include <memory>

#include "base/run_loop.h"
#include "base/test/gmock_callback_support.h"
#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ads_database_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/test/creative_notification_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/notification_ad_serving_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/test/permission_rules_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/test/notification_ad_serving_delegate_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/anti_targeting/resource/anti_targeting_resource.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/geographical/subdivision/subdivision_targeting.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsNotificationAdServingTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    ads_client_notifier_.NotifyBrowserDidBecomeActive();

    ads_client_notifier_.NotifyDidInitializeAds();
  }

  void MaybeServeAd() {
    SubdivisionTargeting subdivision_targeting;
    AntiTargetingResource anti_targeting_resource;
    ad_serving_ = std::make_unique<NotificationAdServing>(
        subdivision_targeting, anti_targeting_resource);
    ad_serving_->SetDelegate(&delegate_mock_);

    ad_serving_->MaybeServeAd();
  }

  ::testing::StrictMock<NotificationAdServingDelegateMock> delegate_mock_;
  std::unique_ptr<NotificationAdServing> ad_serving_;
};

TEST_F(CatsxpAdsNotificationAdServingTest, DoNotServeAdForUnsupportedVersion) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kNotificationAdServingFeature, {{"version", "0"}});

  test::ForcePermissionRules();

  const CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  database::SaveCreativeNotificationAds({creative_ad});

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnFailedToServeNotificationAd)
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  MaybeServeAd();
  run_loop.Run();
}

TEST_F(CatsxpAdsNotificationAdServingTest, ServeAd) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kNotificationAdServingFeature);

  test::ForcePermissionRules();

  const CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  database::SaveCreativeNotificationAds({creative_ad});

  // Act & Assert
  base::RunLoop run_loop1;
  EXPECT_CALL(delegate_mock_, OnOpportunityAroseToServeNotificationAd)
      .WillOnce(base::test::RunOnceClosure(run_loop1.QuitClosure()));
  base::RunLoop run_loop2;
  EXPECT_CALL(delegate_mock_, OnDidServeNotificationAd)
      .WillOnce(base::test::RunOnceClosure(run_loop2.QuitClosure()));
  MaybeServeAd();
  run_loop1.Run();
  run_loop2.Run();
}

TEST_F(CatsxpAdsNotificationAdServingTest, DoNotServeAdIfNoEligibleAdsFound) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kNotificationAdServingFeature);

  test::ForcePermissionRules();

  // Act & Assert
  base::RunLoop run_loop1;
  EXPECT_CALL(delegate_mock_, OnOpportunityAroseToServeNotificationAd)
      .WillOnce(base::test::RunOnceClosure(run_loop1.QuitClosure()));
  base::RunLoop run_loop2;
  EXPECT_CALL(delegate_mock_, OnFailedToServeNotificationAd)
      .WillOnce(base::test::RunOnceClosure(run_loop2.QuitClosure()));
  MaybeServeAd();
  run_loop1.Run();
  run_loop2.Run();
}

TEST_F(CatsxpAdsNotificationAdServingTest,
       DoNotServeAdIfNotAllowedDueToPermissionRules) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kNotificationAdServingFeature);

  const CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*use_random_uuids=*/true);
  database::SaveCreativeNotificationAds({creative_ad});

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnFailedToServeNotificationAd)
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  MaybeServeAd();
  run_loop.Run();
}

}  // namespace catsxp_ads
