/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include <cstddef>
#include <string>

#include "base/check.h"
#include "base/run_loop.h"
#include "base/test/gmock_callback_support.h"
#include "base/test/test_future.h"
#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposit_info.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposits_database_table.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_handler.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_database_table.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/search_result_ads/test/creative_search_result_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/search_result_ads/search_result_ad_event_handler.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/search_result_ads/test/search_result_ad_event_handler_delegate_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/test/ad_event_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

void VerifyDepositForCreativeInstanceIdExpectation(
    const std::string& creative_instance_id) {
  base::test::TestFuture<bool, std::optional<DepositInfo>> test_future;
  const database::table::Deposits database_table;
  database_table.GetForCreativeInstanceId(creative_instance_id,
                                          test_future.GetCallback());
  const auto [_, deposit] = test_future.Take();
  EXPECT_EQ(deposit, std::nullopt);
}

void VerifyCreativeSetConversionExpectation(size_t expected_count) {
  base::test::TestFuture<bool, CreativeSetConversionList> test_future;
  const database::table::CreativeSetConversions database_table;
  database_table.GetUnexpired(
      test_future.GetCallback<bool, const CreativeSetConversionList&>());
  const auto [success, creative_set_conversions] = test_future.Take();
  EXPECT_TRUE(success);
  EXPECT_THAT(creative_set_conversions, ::testing::SizeIs(expected_count));
}

}  // namespace

class CatsxpAdsSearchResultAdEventHandlerForNonRewardsTest
    : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    test::DisableCatsxpRewards();

    event_handler_.SetDelegate(&delegate_mock_);
  }

  void FireEventAndVerifyExpectations(
      const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad,
      mojom::SearchResultAdEventType mojom_ad_event_type,
      bool should_fire_event) {
    CHECK(mojom_creative_ad);

    base::test::TestFuture<bool, std::string, mojom::SearchResultAdEventType>
        test_future;
    event_handler_.FireEvent(
        mojom_creative_ad.Clone(), mojom_ad_event_type,
        test_future.GetCallback<bool, const std::string&,
                                mojom::SearchResultAdEventType>());
    const auto [success, placement_id, ad_event_type] = test_future.Take();
    EXPECT_EQ(should_fire_event, success);
    EXPECT_EQ(mojom_creative_ad->placement_id, placement_id);
    EXPECT_EQ(mojom_ad_event_type, ad_event_type);

    size_t expected_count = 0;

    if (should_fire_event &&
        mojom_ad_event_type == mojom::SearchResultAdEventType::kClicked) {
      const SearchResultAdInfo ad =
          FromMojomBuildSearchResultAd(mojom_creative_ad);
      expected_count =
          mojom_creative_ad->creative_set_conversion && ad.IsValid() ? 1 : 0;
    }

    VerifyDepositForCreativeInstanceIdExpectation(
        mojom_creative_ad->creative_instance_id);

    VerifyCreativeSetConversionExpectation(expected_count);
  }

  SearchResultAdEventHandler event_handler_;
  ::testing::StrictMock<SearchResultAdEventHandlerDelegateMock> delegate_mock_;
};

TEST_F(CatsxpAdsSearchResultAdEventHandlerForNonRewardsTest,
       DoNotFireServedEventWithoutConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAd(
          /*use_random_uuids=*/true);
  const SearchResultAdInfo ad = FromMojomBuildSearchResultAd(mojom_creative_ad);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_,
              OnFailedToFireSearchResultAdEvent(
                  ad, mojom::SearchResultAdEventType::kServedImpression))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      mojom_creative_ad, mojom::SearchResultAdEventType::kServedImpression,
      /*should_fire_event=*/false);
  run_loop.Run();
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerForNonRewardsTest,
       DoNotFireServedEventWithConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);
  const SearchResultAdInfo ad = FromMojomBuildSearchResultAd(mojom_creative_ad);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_,
              OnFailedToFireSearchResultAdEvent(
                  ad, mojom::SearchResultAdEventType::kServedImpression))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      mojom_creative_ad, mojom::SearchResultAdEventType::kServedImpression,
      /*should_fire_event=*/false);
  run_loop.Run();
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerForNonRewardsTest,
       DoNotFireViewedEventWithoutConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAd(
          /*use_random_uuids=*/true);
  const SearchResultAdInfo ad = FromMojomBuildSearchResultAd(mojom_creative_ad);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_,
              OnFailedToFireSearchResultAdEvent(
                  ad, mojom::SearchResultAdEventType::kViewedImpression))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      mojom_creative_ad, mojom::SearchResultAdEventType::kViewedImpression,
      /*should_fire_event=*/false);
  run_loop.Run();
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerForNonRewardsTest,
       DoNotFireViewedEventWithConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);
  const SearchResultAdInfo ad = FromMojomBuildSearchResultAd(mojom_creative_ad);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_,
              OnFailedToFireSearchResultAdEvent(
                  ad, mojom::SearchResultAdEventType::kViewedImpression))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      mojom_creative_ad, mojom::SearchResultAdEventType::kViewedImpression,
      /*should_fire_event=*/false);
  run_loop.Run();
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerForNonRewardsTest,
       DoNotFireClickedEventWithoutConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAd(/*use_random_uuids=*/true);
  const SearchResultAdInfo ad = FromMojomBuildSearchResultAd(mojom_creative_ad);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnFailedToFireSearchResultAdEvent(
                                  ad, mojom::SearchResultAdEventType::kClicked))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(mojom_creative_ad,
                                 mojom::SearchResultAdEventType::kClicked,
                                 /*should_fire_event=*/false);
  run_loop.Run();
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerForNonRewardsTest,
       FireClickedEventWithConversion) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);
  const SearchResultAdInfo ad = FromMojomBuildSearchResultAd(mojom_creative_ad);

  // Act & Assert
  base::RunLoop run_loop;
  ::testing::InSequence seq;
  EXPECT_CALL(delegate_mock_, OnWillFireSearchResultAdClickedEvent(ad));
  EXPECT_CALL(delegate_mock_, OnDidFireSearchResultAdClickedEvent(ad))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(mojom_creative_ad,
                                 mojom::SearchResultAdEventType::kClicked,
                                 /*should_fire_event=*/true);
  run_loop.Run();
}

TEST_F(
    CatsxpAdsSearchResultAdEventHandlerForNonRewardsTest,
    ClickedEventNotifiesDelegateBeforeRecordingCompletesToEnsurePageLandIsRecorded) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);
  const SearchResultAdInfo ad = FromMojomBuildSearchResultAd(mojom_creative_ad);

  bool delegate_was_notified = false;
  ::testing::InSequence seq;
  EXPECT_CALL(delegate_mock_, OnWillFireSearchResultAdClickedEvent(ad))
      .WillOnce([&] { delegate_was_notified = true; });
  EXPECT_CALL(delegate_mock_, OnDidFireSearchResultAdClickedEvent(ad));

  base::test::TestFuture<bool, std::string, mojom::SearchResultAdEventType>
      test_future;

  // Act & Assert
  event_handler_.FireEvent(
      mojom_creative_ad.Clone(), mojom::SearchResultAdEventType::kClicked,
      test_future.GetCallback<bool, const std::string&,
                              mojom::SearchResultAdEventType>());
  const auto [success, placement_id, mojom_ad_event_type] = test_future.Take();
  EXPECT_TRUE(delegate_was_notified);
  EXPECT_TRUE(success);
  EXPECT_EQ(mojom_creative_ad->placement_id, placement_id);
  EXPECT_EQ(mojom::SearchResultAdEventType::kClicked, mojom_ad_event_type);
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerForNonRewardsTest,
       DoNotFireClickedEventIfAdPlacementWasAlreadyClicked) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);
  const SearchResultAdInfo ad = FromMojomBuildSearchResultAd(mojom_creative_ad);
  test::RecordAdEvent(ad, mojom::ConfirmationType::kClicked);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnFailedToFireSearchResultAdEvent(
                                  ad, mojom::SearchResultAdEventType::kClicked))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(mojom_creative_ad,
                                 mojom::SearchResultAdEventType::kClicked,
                                 /*should_fire_event=*/false);
  run_loop.Run();
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerForNonRewardsTest,
       DoNotFireClickedEventWithInvalidPlacementId) {
  // Arrange
  mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);
  mojom_creative_ad->placement_id = test::kInvalidPlacementId;
  const SearchResultAdInfo ad = FromMojomBuildSearchResultAd(mojom_creative_ad);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnFailedToFireSearchResultAdEvent(
                                  ad, mojom::SearchResultAdEventType::kClicked))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(mojom_creative_ad,
                                 mojom::SearchResultAdEventType::kClicked,
                                 /*should_fire_event=*/false);
  run_loop.Run();
}

TEST_F(CatsxpAdsSearchResultAdEventHandlerForNonRewardsTest,
       DoNotFireClickedEventWithInvalidCreativeInstanceId) {
  // Arrange
  mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*use_random_uuids=*/true);
  mojom_creative_ad->creative_instance_id = test::kInvalidCreativeInstanceId;
  const SearchResultAdInfo ad = FromMojomBuildSearchResultAd(mojom_creative_ad);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnFailedToFireSearchResultAdEvent(
                                  ad, mojom::SearchResultAdEventType::kClicked))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(mojom_creative_ad,
                                 mojom::SearchResultAdEventType::kClicked,
                                 /*should_fire_event=*/false);
  run_loop.Run();
}

}  // namespace catsxp_ads
