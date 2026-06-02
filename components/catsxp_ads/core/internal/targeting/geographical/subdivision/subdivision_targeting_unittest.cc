/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/geographical/subdivision/subdivision_targeting.h"

#include <memory>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/subdivision.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/subdivision_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/test/subdivision_url_request_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/geographical/subdivision/subdivision_targeting_constants.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "net/http/http_status_code.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSubdivisionTargetingTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    subdivision_targeting_ = std::make_unique<SubdivisionTargeting>();
    subdivision_ = std::make_unique<Subdivision>();
    subdivision_->AddObserver(subdivision_targeting_.get());
  }

  void MockHttpOkUrlResponse(const std::string& country_code,
                             const std::string& subdivision_code) {
    const test::URLResponseMap url_responses = {
        {BuildSubdivisionUrlPath(),
         {{net::HTTP_OK, test::BuildSubdivisionUrlResponseBody(
                             country_code, subdivision_code)}}}};
    test::MockUrlResponses(ads_client_mock_, url_responses);
  }

  std::unique_ptr<SubdivisionTargeting> subdivision_targeting_;
  std::unique_ptr<Subdivision> subdivision_;
};

TEST_F(CatsxpAdsSubdivisionTargetingTest,
       AllowAndFetchWhenOptingInToNotificationAds) {
  // Arrange
  test::OptOutOfAllAds();

  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  ads_client_notifier_.NotifyDidInitializeAds();

  // Act
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, true);

  // Assert
  EXPECT_TRUE(SubdivisionTargeting::ShouldAllow());
  EXPECT_FALSE(subdivision_targeting_->IsDisabled());
  EXPECT_TRUE(subdivision_targeting_->ShouldAutoDetect());
  EXPECT_EQ("US-CA", GetProfileStringPref(
                         prefs::kSubdivisionTargetingAutoDetectedSubdivision));
}

TEST_F(CatsxpAdsSubdivisionTargetingTest,
       DoNotFetchWhenOptingOutOfNotificationAds) {
  // Arrange
  test::OptOutOfAllAds();

  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  ads_client_notifier_.NotifyDidInitializeAds();

  // Act & Assert
  EXPECT_CALL(ads_client_mock_, UrlRequest).Times(0);
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, false);
}

TEST_F(CatsxpAdsSubdivisionTargetingTest,
       ShouldAllowAndAutoDetectForSupportedCountryAndRegionUrlResponse) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(SubdivisionTargeting::ShouldAllow());
  EXPECT_FALSE(subdivision_targeting_->IsDisabled());
  EXPECT_TRUE(subdivision_targeting_->ShouldAutoDetect());
  EXPECT_EQ("US-CA", GetProfileStringPref(
                         prefs::kSubdivisionTargetingAutoDetectedSubdivision));
}

TEST_F(
    CatsxpAdsSubdivisionTargetingTest,
    ShouldAllowButDefaultToDisabledForSupportedCountryButNoRegionUrlResponse) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"US",
                        /*subdivision_code=*/"NO REGION");

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(SubdivisionTargeting::ShouldAllow());
  EXPECT_TRUE(subdivision_targeting_->IsDisabled());
  EXPECT_FALSE(subdivision_targeting_->ShouldAutoDetect());
}

TEST_F(CatsxpAdsSubdivisionTargetingTest,
       ShouldAutoDetectForUnsupportedCountryAndRegionUrlResponse) {
  // Arrange
  MockHttpOkUrlResponse(/*country_code=*/"XX", /*subdivision_code=*/"XX");

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_FALSE(SubdivisionTargeting::ShouldAllow());
  EXPECT_FALSE(subdivision_targeting_->IsDisabled());
  EXPECT_TRUE(subdivision_targeting_->ShouldAutoDetect());
}

TEST_F(CatsxpAdsSubdivisionTargetingTest,
       ShouldAllowIfDisabledAndCountryIsSupported) {
  // Arrange
  test::SetProfileStringPrefValue(
      prefs::kSubdivisionTargetingUserSelectedSubdivision,
      kSubdivisionTargetingDisabled);
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(SubdivisionTargeting::ShouldAllow());
  EXPECT_TRUE(subdivision_targeting_->IsDisabled());
  EXPECT_FALSE(subdivision_targeting_->ShouldAutoDetect());
}

TEST_F(CatsxpAdsSubdivisionTargetingTest,
       ShouldAllowIfDisabledAndCountryIsUnsupported) {
  // Arrange
  test::SetProfileStringPrefValue(
      prefs::kSubdivisionTargetingUserSelectedSubdivision,
      kSubdivisionTargetingDisabled);
  MockHttpOkUrlResponse(/*country_code=*/"XX", /*subdivision_code=*/"XX");

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_FALSE(SubdivisionTargeting::ShouldAllow());
  EXPECT_TRUE(subdivision_targeting_->IsDisabled());
  EXPECT_FALSE(subdivision_targeting_->ShouldAutoDetect());
}

TEST_F(CatsxpAdsSubdivisionTargetingTest,
       ShouldAllowAndAutoDetectIfCountryIsSupported) {
  // Arrange
  test::SetProfileStringPrefValue(
      prefs::kSubdivisionTargetingAutoDetectedSubdivision, "US-CA");

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(SubdivisionTargeting::ShouldAllow());
  EXPECT_FALSE(subdivision_targeting_->IsDisabled());
  EXPECT_TRUE(subdivision_targeting_->ShouldAutoDetect());
  EXPECT_EQ("US-CA", GetProfileStringPref(
                         prefs::kSubdivisionTargetingAutoDetectedSubdivision));
}

TEST_F(CatsxpAdsSubdivisionTargetingTest,
       ShouldAllowAndAutoDetectIfSubdivisionCodeIsUnsupported) {
  // Arrange
  test::SetProfileStringPrefValue(
      prefs::kSubdivisionTargetingAutoDetectedSubdivision, "XX-XX");

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_FALSE(SubdivisionTargeting::ShouldAllow());
  EXPECT_FALSE(subdivision_targeting_->IsDisabled());
  EXPECT_TRUE(subdivision_targeting_->ShouldAutoDetect());
  EXPECT_EQ("XX-XX", GetProfileStringPref(
                         prefs::kSubdivisionTargetingAutoDetectedSubdivision));
}

TEST_F(CatsxpAdsSubdivisionTargetingTest,
       ShouldNotAllowIfLocaleIsUnsupportedAndSubdivisionCodeIsEmpty) {
  // Arrange
  fake_locale_.SetCountryCode("XX");

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_FALSE(SubdivisionTargeting::ShouldAllow());
  EXPECT_FALSE(subdivision_targeting_->IsDisabled());
  EXPECT_TRUE(subdivision_targeting_->ShouldAutoDetect());
}

TEST_F(CatsxpAdsSubdivisionTargetingTest, ShouldAllowIfSubdivisionCodeNotValid) {
  // Arrange
  test::SetProfileStringPrefValue(
      prefs::kSubdivisionTargetingAutoDetectedSubdivision, "CA-NO REGION");

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(SubdivisionTargeting::ShouldAllow());
  EXPECT_TRUE(subdivision_targeting_->IsDisabled());
  EXPECT_FALSE(subdivision_targeting_->ShouldAutoDetect());
}

TEST_F(CatsxpAdsSubdivisionTargetingTest,
       ShouldAutoDetectAndNotAllowIfSubdivisionCodeIsEmpty) {
  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_FALSE(SubdivisionTargeting::ShouldAllow());
  EXPECT_FALSE(subdivision_targeting_->IsDisabled());
  EXPECT_TRUE(subdivision_targeting_->ShouldAutoDetect());
}

TEST_F(CatsxpAdsSubdivisionTargetingTest,
       RetryAfterInvalidUrlResponseStatusCode) {
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

  ads_client_notifier_.NotifyDidInitializeAds();

  // Act
  FastForwardClockToNextPendingTask();

  // Assert
  EXPECT_TRUE(SubdivisionTargeting::ShouldAllow());
  EXPECT_FALSE(subdivision_targeting_->IsDisabled());
  EXPECT_EQ("US-CA", GetProfileStringPref(
                         prefs::kSubdivisionTargetingAutoDetectedSubdivision));
}

TEST_F(CatsxpAdsSubdivisionTargetingTest,
       ShouldAllowWhenUserSelectSubdivisionWithSameCountry) {
  // Arrange
  test::SetProfileStringPrefValue(
      prefs::kSubdivisionTargetingUserSelectedSubdivision, "US-FL");
  MockHttpOkUrlResponse(/*country_code=*/"US", /*subdivision_code=*/"CA");

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(SubdivisionTargeting::ShouldAllow());
  EXPECT_FALSE(subdivision_targeting_->IsDisabled());
  EXPECT_FALSE(subdivision_targeting_->ShouldAutoDetect());
  EXPECT_EQ("US-CA", GetProfileStringPref(
                         prefs::kSubdivisionTargetingAutoDetectedSubdivision));
  EXPECT_EQ("US-FL", GetProfileStringPref(
                         prefs::kSubdivisionTargetingUserSelectedSubdivision));
  EXPECT_EQ("US-FL", subdivision_targeting_->GetSubdivision());
}

TEST_F(CatsxpAdsSubdivisionTargetingTest,
       ShouldAllowWhenUserSelectSubdivisionAndAutodetectedCountryIsSupported) {
  // Arrange
  test::SetProfileStringPrefValue(
      prefs::kSubdivisionTargetingUserSelectedSubdivision, "US-FL");
  MockHttpOkUrlResponse(/*country_code=*/"CA", /*subdivision_code=*/"AB");

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_TRUE(SubdivisionTargeting::ShouldAllow());
  EXPECT_FALSE(subdivision_targeting_->IsDisabled());
  EXPECT_TRUE(subdivision_targeting_->ShouldAutoDetect());
  EXPECT_EQ("CA-AB", GetProfileStringPref(
                         prefs::kSubdivisionTargetingAutoDetectedSubdivision));
}

TEST_F(
    CatsxpAdsSubdivisionTargetingTest,
    ShouldNotAllowWhenUserSelectSubdivisionAndAutodetectedCountryIsUnsupported) {
  // Arrange
  test::SetProfileStringPrefValue(
      prefs::kSubdivisionTargetingUserSelectedSubdivision, "US-FL");
  MockHttpOkUrlResponse(/*country_code=*/"XX", /*subdivision_code=*/"XX");

  // Act
  ads_client_notifier_.NotifyDidInitializeAds();

  // Assert
  EXPECT_FALSE(SubdivisionTargeting::ShouldAllow());
  EXPECT_FALSE(subdivision_targeting_->IsDisabled());
  EXPECT_FALSE(subdivision_targeting_->ShouldAutoDetect());
  EXPECT_EQ("XX-XX", GetProfileStringPref(
                         prefs::kSubdivisionTargetingAutoDetectedSubdivision));
  EXPECT_EQ("US-FL", GetProfileStringPref(
                         prefs::kSubdivisionTargetingUserSelectedSubdivision));
  EXPECT_EQ("US-FL", subdivision_targeting_->GetSubdivision());
}

class CatsxpAdsSubdivisionTargetingRetryOnInvalidUrlResponseBodyTest
    : public CatsxpAdsSubdivisionTargetingTest,
      public ::testing::WithParamInterface<const char*> {};

TEST_P(CatsxpAdsSubdivisionTargetingRetryOnInvalidUrlResponseBodyTest,
       RetryAfterInvalidUrlResponseBody) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(),
       {{net::HTTP_OK, /*response_body=*/GetParam()},
        {net::HTTP_OK,
         test::BuildSubdivisionUrlResponseBody(
             /*country_code=*/"US", /*subdivision_code=*/"CA")}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  ads_client_notifier_.NotifyDidInitializeAds();

  // Act
  FastForwardClockToNextPendingTask();

  // Assert
  EXPECT_TRUE(SubdivisionTargeting::ShouldAllow());
  EXPECT_FALSE(subdivision_targeting_->IsDisabled());
  EXPECT_EQ("US-CA", GetProfileStringPref(
                         prefs::kSubdivisionTargetingAutoDetectedSubdivision));
}

INSTANTIATE_TEST_SUITE_P(
    ,
    CatsxpAdsSubdivisionTargetingRetryOnInvalidUrlResponseBodyTest,
    ::testing::Values("",
                      "MALFORMED",
                      "{}",
                      "{MALFORMED}",
                      R"({"country":"US","region":""})",
                      R"({"country":"","region":"CA"})",
                      R"({"country":"","region":""})",
                      R"({"country":"US"})",
                      R"({"region":"CA"})"));

}  // namespace catsxp_ads
