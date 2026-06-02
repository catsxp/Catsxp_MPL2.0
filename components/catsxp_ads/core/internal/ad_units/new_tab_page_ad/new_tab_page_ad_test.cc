/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include <optional>

#include "base/run_loop.h"
#include "base/test/gmock_callback_support.h"
#include "base/test/mock_callback.h"
#include "base/test/scoped_feature_list.h"
#include "base/test/test_future.h"
#include "base/test/values_test_util.h"
#include "base/types/optional_ref.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/new_tab_page_ad_serving_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/test/permission_rules_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"
#include "catsxp/components/catsxp_ads/core/public/ads.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsNewTabPageAdIntegrationTest : public test::TestBase {
 public:
  CatsxpAdsNewTabPageAdIntegrationTest()
      : test::TestBase(/*is_integration_test=*/true) {}

 protected:
  void SetUp() override {
    AdvanceClockTo(test::TimeFromUTCString("Fri, 31 Jan 2025 16:28"));

    test::TestBase::SetUp();
  }

  void MockCreativeNewTabPageAds() {
    const std::string json = R"JSON(
      {
        "schemaVersion": 2,
        "campaigns": [
          {
            "version": 1,
            "campaignId": "65933e82-6b21-440b-9956-c0f675ca7435",
            "advertiserId": "496b045a-195e-441f-b439-07bac083450f",
            "startAt": "2024-01-31T00:00:00Z",
            "endAt": "2025-01-31T23:59:59Z",
            "dailyCap": 20,
            "priority": 10,
            "ptr": 1,
            "geoTargets": [
              "US"
            ],
            "dayParts": [
              {
                "daysOfWeek": "0123456",
                "startMinute": 0,
                "endMinute": 1439
              }
            ],
            "creativeSets": [
              {
                "creativeSetId": "34ab06be-c9ed-4104-9ce0-9e639f4ad272",
                "creatives": [
                  {
                    "creativeInstanceId": "aa0b561e-9eed-4aaa-8999-5627bc6b14fd",
                    "companyName": "Rich Media NTT Creative",
                    "alt": "Some rich content",
                    "targetUrl": "https://catsxp.com",
                    "wallpaper": {
                      "type": "richMedia",
                      "relativeUrl": "aa0b561e-9eed-4aaa-8999-5627bc6b14fd/index.html"
                    }
                  },
                  {
                    "creativeInstanceId": "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
                    "companyName": "Image NTT Creative",
                    "alt": "Some content",
                    "targetUrl": "https://basicattentiontoken.org",
                    "wallpaper": {
                      "type": "image",
                      "relativeUrl": "546fe7b0-5047-4f28-a11c-81f14edcf0f6/background.jpg",
                      "focalPoint": {
                        "x": 25,
                        "y": 50
                      },
                      "button": {
                        "image": {
                          "relativeUrl": "546fe7b0-5047-4f28-a11c-81f14edcf0f6/button.png"
                        }
                      }
                    }
                  }
                ],
                "conversions": [
                  {
                    "observationWindow": 30,
                    "urlPattern": "https://www.catsxp.com/*"
                  }
                ],
                "perDay": 20,
                "perWeek": 140,
                "perMonth": 560,
                "totalMax": 1000,
                "value": "0.1"
              }
            ]
          }
        ]
      }
    )JSON";

    base::test::TestFuture<bool> test_future;
    base::DictValue dict = base::test::ParseJsonDict(json);
    GetAds().ParseAndSaveNewTabPageAds(std::move(dict),
                                       test_future.GetCallback());
    EXPECT_TRUE(test_future.Get());
  }

  void TriggerNewTabPageAdEventAndVerifiyExpectations(
      const std::string& placement_id,
      const std::string& creative_instance_id,
      mojom::NewTabPageAdEventType mojom_ad_event_type,
      bool should_fire_event) {
    base::MockCallback<ResultCallback> callback;
    base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
    EXPECT_CALL(callback, Run(/*success=*/should_fire_event))
        .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
    GetAds().TriggerNewTabPageAdEvent(
        placement_id, creative_instance_id,
        mojom::NewTabPageAdMetricType::kConfirmation, mojom_ad_event_type,
        callback.Get());
    run_loop.Run();
  }
};

TEST_F(CatsxpAdsNewTabPageAdIntegrationTest, ServeAd) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      {kNewTabPageAdServingFeature});

  test::ForcePermissionRules();

  MockCreativeNewTabPageAds();

  // Act & Assert
  base::MockCallback<MaybeServeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*ad=*/::testing::Ne(std::nullopt)))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  GetAds().MaybeServeNewTabPageAd(callback.Get());
  run_loop.Run();
}

TEST_F(CatsxpAdsNewTabPageAdIntegrationTest,
       AlwaysServeAdIfUserHasJoinedCatsxpRewardsAndNotConnectedWallet) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      {kNewTabPageAdServingFeature});

  test::DisconnectExternalCatsxpRewardsWallet();

  MockCreativeNewTabPageAds();

  // Act & Assert
  base::MockCallback<MaybeServeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*ad=*/::testing::Ne(std::nullopt)))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  GetAds().MaybeServeNewTabPageAd(callback.Get());
  run_loop.Run();
}

TEST_F(CatsxpAdsNewTabPageAdIntegrationTest,
       DoNotServeAdIfPermissionRulesAreDenied) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      {kNewTabPageAdServingFeature});

  MockCreativeNewTabPageAds();

  // Act & Assert
  base::MockCallback<MaybeServeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*ad=*/::testing::Eq(std::nullopt)))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  GetAds().MaybeServeNewTabPageAd(callback.Get());
  run_loop.Run();
}

TEST_F(CatsxpAdsNewTabPageAdIntegrationTest,
       DoNotServeAdIfUserHasNotOptedInToNewTabPageAds) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      {kNewTabPageAdServingFeature});

  test::ForcePermissionRules();

  test::OptOutOfNewTabPageAds();

  MockCreativeNewTabPageAds();

  // Act & Assert
  base::MockCallback<MaybeServeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*ad=*/::testing::Eq(std::nullopt)))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  GetAds().MaybeServeNewTabPageAd(callback.Get());
  run_loop.Run();
}

TEST_F(CatsxpAdsNewTabPageAdIntegrationTest, TriggerViewedEvent) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      {kNewTabPageAdServingFeature});

  test::ForcePermissionRules();

  MockCreativeNewTabPageAds();

  base::MockCallback<MaybeServeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run)
      .WillOnce([&](base::optional_ref<const NewTabPageAdInfo> ad) {
        ASSERT_TRUE(ad);
        ASSERT_TRUE(ad->IsValid());

        // Act & Assert
        TriggerNewTabPageAdEventAndVerifiyExpectations(
            ad->placement_id, ad->creative_instance_id,
            mojom::NewTabPageAdEventType::kViewedImpression,
            /*should_fire_event=*/true);
        run_loop.Quit();
      });

  GetAds().MaybeServeNewTabPageAd(callback.Get());
  run_loop.Run();
}

TEST_F(CatsxpAdsNewTabPageAdIntegrationTest,
       TriggerViewedEventForNonRewardsUser) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      {kNewTabPageAdServingFeature});

  test::DisableCatsxpRewards();

  MockCreativeNewTabPageAds();

  base::MockCallback<MaybeServeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run)
      .WillOnce([&](base::optional_ref<const NewTabPageAdInfo> ad) {
        ASSERT_TRUE(ad);
        ASSERT_TRUE(ad->IsValid());

        // Act & Assert
        TriggerNewTabPageAdEventAndVerifiyExpectations(
            ad->placement_id, ad->creative_instance_id,
            mojom::NewTabPageAdEventType::kViewedImpression,
            /*should_fire_event=*/true);
        run_loop.Quit();
      });

  GetAds().MaybeServeNewTabPageAd(callback.Get());
  run_loop.Run();
}

TEST_F(CatsxpAdsNewTabPageAdIntegrationTest, TriggerClickedEvent) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      {kNewTabPageAdServingFeature});

  test::ForcePermissionRules();

  MockCreativeNewTabPageAds();

  base::MockCallback<MaybeServeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run)
      .WillOnce([&](base::optional_ref<const NewTabPageAdInfo> ad) {
        ASSERT_TRUE(ad);
        ASSERT_TRUE(ad->IsValid());

        TriggerNewTabPageAdEventAndVerifiyExpectations(
            ad->placement_id, ad->creative_instance_id,
            mojom::NewTabPageAdEventType::kViewedImpression,
            /*should_fire_event=*/true);

        // Act & Assert
        TriggerNewTabPageAdEventAndVerifiyExpectations(
            ad->placement_id, ad->creative_instance_id,
            mojom::NewTabPageAdEventType::kClicked,
            /*should_fire_event=*/true);
        run_loop.Quit();
      });

  GetAds().MaybeServeNewTabPageAd(callback.Get());
  run_loop.Run();
}

TEST_F(CatsxpAdsNewTabPageAdIntegrationTest,
       TriggerClickedEventForNonRewardsUser) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      {kNewTabPageAdServingFeature});

  test::DisableCatsxpRewards();

  MockCreativeNewTabPageAds();

  base::MockCallback<MaybeServeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run)
      .WillOnce([&](base::optional_ref<const NewTabPageAdInfo> ad) {
        ASSERT_TRUE(ad);
        ASSERT_TRUE(ad->IsValid());

        TriggerNewTabPageAdEventAndVerifiyExpectations(
            ad->placement_id, ad->creative_instance_id,
            mojom::NewTabPageAdEventType::kViewedImpression,
            /*should_fire_event=*/true);

        // Act & Assert
        TriggerNewTabPageAdEventAndVerifiyExpectations(
            ad->placement_id, ad->creative_instance_id,
            mojom::NewTabPageAdEventType::kClicked,
            /*should_fire_event=*/true);
        run_loop.Quit();
      });

  GetAds().MaybeServeNewTabPageAd(callback.Get());
  run_loop.Run();
}

TEST_F(CatsxpAdsNewTabPageAdIntegrationTest,
       DoNotTriggerEventForInvalidCreativeInstanceId) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      {kNewTabPageAdServingFeature});

  test::ForcePermissionRules();

  MockCreativeNewTabPageAds();

  base::MockCallback<MaybeServeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run)
      .WillOnce([&](base::optional_ref<const NewTabPageAdInfo> ad) {
        ASSERT_TRUE(ad);
        ASSERT_TRUE(ad->IsValid());

        // Act & Assert
        TriggerNewTabPageAdEventAndVerifiyExpectations(
            ad->placement_id, test::kInvalidCreativeInstanceId,
            mojom::NewTabPageAdEventType::kViewedImpression,
            /*should_fire_event=*/false);
        run_loop.Quit();
      });

  GetAds().MaybeServeNewTabPageAd(callback.Get());
  run_loop.Run();
}

}  // namespace catsxp_ads
