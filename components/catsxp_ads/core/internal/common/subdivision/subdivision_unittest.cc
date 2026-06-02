/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/subdivision.h"

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/test/subdivision_observer_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/subdivision_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/test/subdivision_url_request_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "catsxp/components/catsxp_rewards/core/pref_names.h"
#include "catsxp/components/ntp_background_images/common/pref_names.h"
#include "net/http/http_status_code.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSubdivisionTest : public test::TestBase {
 public:
  void SetUp() override {
    test::TestBase::SetUp();

    subdivision_ = std::make_unique<Subdivision>();
    subdivision_->AddObserver(&subdivision_observer_mock_);
  }

  void TearDown() override {
    subdivision_->RemoveObserver(&subdivision_observer_mock_);

    test::TestBase::TearDown();
  }

  void MockHttpOkUrlResponse(const std::string& country_code,
                             const std::string& subdivision_code) {
    const test::URLResponseMap url_responses = {
        {BuildSubdivisionUrlPath(),
         {{net::HTTP_OK, test::BuildSubdivisionUrlResponseBody(
                             country_code, subdivision_code)}}}};
    test::MockUrlResponses(ads_client_mock_, url_responses);
  }

 protected:
  std::unique_ptr<Subdivision> subdivision_;

  SubdivisionObserverMock subdivision_observer_mock_;
};

TEST_F(CatsxpAdsSubdivisionTest, OnDidInitializeAds) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision("US-CA"));

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(CatsxpAdsSubdivisionTest, FetchIfUserJoinsCatsxpRewards) {
  // Arrange
  test::DisableCatsxpRewards();

  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision);

  // Act & Assert
  SetProfileBooleanPref(catsxp_rewards::prefs::kEnabled, true);
}

TEST_F(CatsxpAdsSubdivisionTest, DoNotFetchIfUserHasNotJoinedCatsxpRewards) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(catsxp_rewards::prefs::kEnabled, false);
}

TEST_F(CatsxpAdsSubdivisionTest, DoNotFetchWhenOptingOutOfNotificationAds) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, false);
}

TEST_F(CatsxpAdsSubdivisionTest, FetchWhenOptingInToNotificationAds) {
  // Arrange
  test::OptOutOfAllAds();

  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision);

  // Act & Assert
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, true);
}

TEST_F(CatsxpAdsSubdivisionTest, DoNotFetchWhenOptingOutOfNewTabPageAds) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(
      ntp_background_images::prefs::kNewTabPageShowBackgroundImage, false);
  SetProfileBooleanPref(ntp_background_images::prefs::
                            kNewTabPageShowSponsoredImagesBackgroundImage,
                        false);
}

TEST_F(CatsxpAdsSubdivisionTest, DoNotFetchWhenOptingInToNewTabPageAds) {
  // Arrange
  test::OptOutOfAllAds();

  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(
      ntp_background_images::prefs::kNewTabPageShowBackgroundImage, true);
  SetProfileBooleanPref(ntp_background_images::prefs::
                            kNewTabPageShowSponsoredImagesBackgroundImage,
                        true);
}

TEST_F(CatsxpAdsSubdivisionTest, DoNotFetchWhenOptingOutOfSearchResultAds) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(prefs::kOptedInToSearchResultAds, false);
}

TEST_F(CatsxpAdsSubdivisionTest, DoNotFetchWhenOptingInToSearchResultAds) {
  // Arrange
  test::OptOutOfAllAds();

  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act & Assert
  SetProfileBooleanPref(prefs::kOptedInToSearchResultAds, true);
}

TEST_F(CatsxpAdsSubdivisionTest,
       DoNotRetryIfHttpForbiddenUrlResponseStatusCode) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(),
       {{net::HTTP_FORBIDDEN,
         /*response_body=*/std::string(
             net::GetHttpReasonPhrase(net::HTTP_FORBIDDEN))}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  ads_client_notifier_.NotifyDidInitializeAds();

  // Act
  FastForwardClockToNextPendingTask();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(CatsxpAdsSubdivisionTest,
       RetryIfHttpInternalServerErrorResponseStatusCode) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(),
       {{net::HTTP_INTERNAL_SERVER_ERROR,
         /*response_body=*/std::string(
             net::GetHttpReasonPhrase(net::HTTP_INTERNAL_SERVER_ERROR))},
        {net::HTTP_OK,
         test::BuildSubdivisionUrlResponseBody(
             /*country_code=*/"US", /*subdivision_code=*/"CA")}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision("US-CA"));

  ads_client_notifier_.NotifyDidInitializeAds();

  // Act
  FastForwardClockToNextPendingTask();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(CatsxpAdsSubdivisionTest, RetryIfResponseBodyIsInvalid) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(), {{net::HTTP_OK, /*response_body=*/"{}"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(CatsxpAdsSubdivisionTest, NoRegionSubdivisionCode) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US",
                        /*subdivision_code=*/"NO REGION");

  EXPECT_CALL(subdivision_observer_mock_,
              OnDidUpdateSubdivision("US-NO REGION"));

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(CatsxpAdsSubdivisionTest, EmptySubdivisionCode) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(CatsxpAdsSubdivisionTest, EmptyCountryCode) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"", /*subdivision_code=*/"CA");

  EXPECT_CALL(subdivision_observer_mock_, OnDidUpdateSubdivision).Times(0);

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

}  // namespace catsxp_ads
