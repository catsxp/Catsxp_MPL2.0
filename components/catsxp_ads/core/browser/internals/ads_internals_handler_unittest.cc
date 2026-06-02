/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/browser/internals/ads_internals_handler.h"

#include "base/test/bind.h"
#include "base/test/task_environment.h"
#include "base/test/test_future.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/browser/service/ads_service_callback.h"
#include "catsxp/components/catsxp_ads/core/browser/service/test/ads_service_mock.h"
#include "catsxp/components/catsxp_rewards/core/pref_names.h"
#include "catsxp/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/testing_pref_service.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsInternalsHandlerTest : public testing::Test {
 public:
  void SetUp() override {
    profile_prefs_.registry()->RegisterBooleanPref(
        catsxp_rewards::prefs::kEnabled, false);
  }

 protected:
  base::test::TaskEnvironment task_environment_;
  TestingPrefServiceSimple profile_prefs_;
  AdsServiceMock ads_service_mock_;
};

TEST_F(CatsxpAdsInternalsHandlerTest,
       GetAdsInternalsWithNullAdsServiceReturnsEmptyJson) {
  // Arrange
  AdsInternalsHandler handler(/*ads_service=*/nullptr, profile_prefs_);

  mojo::Remote<bat_ads::mojom::AdsInternals> ads_internals_remote;
  handler.BindInterface(ads_internals_remote.BindNewPipeAndPassReceiver());

  base::test::TestFuture<std::string> test_future;

  // Act
  ads_internals_remote->GetAdsInternals(base::BindLambdaForTesting(
      [&test_future](const std::string& json) { test_future.SetValue(json); }));

  // Assert
  EXPECT_EQ("{}", test_future.Get());
}

TEST_F(CatsxpAdsInternalsHandlerTest,
       GetAdsInternalsDelegatesCallbackToAdsService) {
  // Arrange
  AdsInternalsHandler handler(&ads_service_mock_, profile_prefs_);

  mojo::Remote<bat_ads::mojom::AdsInternals> ads_internals_remote;
  handler.BindInterface(ads_internals_remote.BindNewPipeAndPassReceiver());

  EXPECT_CALL(ads_service_mock_, GetInternals)
      .WillOnce([](GetInternalsCallback callback) {
        std::move(callback).Run(base::DictValue().Set("foo", "bar"));
      });

  base::test::TestFuture<std::string> test_future;

  // Act
  ads_internals_remote->GetAdsInternals(base::BindLambdaForTesting(
      [&test_future](const std::string& json) { test_future.SetValue(json); }));

  // Assert
  EXPECT_EQ(R"JSON({"foo":"bar"})JSON", test_future.Get());
}

TEST_F(CatsxpAdsInternalsHandlerTest,
       GetAdsInternalsWithNulloptInternalsReturnsEmptyJson) {
  // Arrange
  AdsInternalsHandler handler(&ads_service_mock_, profile_prefs_);

  mojo::Remote<bat_ads::mojom::AdsInternals> ads_internals_remote;
  handler.BindInterface(ads_internals_remote.BindNewPipeAndPassReceiver());

  EXPECT_CALL(ads_service_mock_, GetInternals)
      .WillOnce([](GetInternalsCallback callback) {
        std::move(callback).Run(/*dict=*/std::nullopt);
      });

  base::test::TestFuture<std::string> test_future;

  // Act
  ads_internals_remote->GetAdsInternals(base::BindLambdaForTesting(
      [&test_future](const std::string& json) { test_future.SetValue(json); }));

  // Assert
  EXPECT_EQ("{}", test_future.Get());
}

TEST_F(CatsxpAdsInternalsHandlerTest,
       ClearAdsDataWithNullAdsServiceRunsCallbackWithFalse) {
  // Arrange
  AdsInternalsHandler handler(/*ads_service=*/nullptr, profile_prefs_);

  mojo::Remote<bat_ads::mojom::AdsInternals> ads_internals_remote;
  handler.BindInterface(ads_internals_remote.BindNewPipeAndPassReceiver());

  base::test::TestFuture<bool> test_future;

  // Act
  ads_internals_remote->ClearAdsData(test_future.GetCallback());

  // Assert
  EXPECT_FALSE(test_future.Get());
}

TEST_F(CatsxpAdsInternalsHandlerTest,
       ClearAdsDataDelegatesCallbackToAdsService) {
  // Arrange
  AdsInternalsHandler handler(&ads_service_mock_, profile_prefs_);

  mojo::Remote<bat_ads::mojom::AdsInternals> ads_internals_remote;
  handler.BindInterface(ads_internals_remote.BindNewPipeAndPassReceiver());

  EXPECT_CALL(ads_service_mock_, ClearData)
      .WillOnce([](ResultCallback callback) {
        std::move(callback).Run(/*success=*/true);
      });

  base::test::TestFuture<bool> test_future;

  // Act
  ads_internals_remote->ClearAdsData(test_future.GetCallback());

  // Assert
  EXPECT_TRUE(test_future.Get());
}

TEST_F(CatsxpAdsInternalsHandlerTest,
       ClearAdsDataRunsCallbackWithFalseOnAdsServiceFailure) {
  // Arrange
  AdsInternalsHandler handler(&ads_service_mock_, profile_prefs_);

  mojo::Remote<bat_ads::mojom::AdsInternals> ads_internals_remote;
  handler.BindInterface(ads_internals_remote.BindNewPipeAndPassReceiver());

  EXPECT_CALL(ads_service_mock_, ClearData)
      .WillOnce([](ResultCallback callback) {
        std::move(callback).Run(/*success=*/false);
      });

  base::test::TestFuture<bool> test_future;

  // Act
  ads_internals_remote->ClearAdsData(test_future.GetCallback());

  // Assert
  EXPECT_FALSE(test_future.Get());
}

}  // namespace catsxp_ads
