/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers.h"

#include <memory>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/test/issuers_delegate_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/test/issuers_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/url_request/issuers_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_constants.h"
#include "net/http/http_status_code.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsIssuersTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    issuers_ = std::make_unique<Issuers>();
    issuers_->SetDelegate(&delegate_mock_);
  }

  std::unique_ptr<Issuers> issuers_;
  IssuersDelegateMock delegate_mock_;
};

TEST_F(CatsxpAdsIssuersTest, FetchIssuers) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildIssuersUrlPath(),
       {{net::HTTP_OK, test::BuildIssuersUrlResponseBody()}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnFailedToFetchIssuers).Times(0);
  EXPECT_CALL(delegate_mock_, OnWillRetryFetchingIssuers).Times(0);
  EXPECT_CALL(delegate_mock_, OnDidRetryFetchingIssuers).Times(0);
  EXPECT_CALL(delegate_mock_, OnDidFetchIssuers(test::BuildIssuers()));
  issuers_->PeriodicallyFetch();
}

TEST_F(CatsxpAdsIssuersTest, DoNotFetchIfInvalidResponseBody) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildIssuersUrlPath(),
       {{net::HTTP_OK, /*response_body=*/test::kMalformedJson}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnFailedToFetchIssuers);
  EXPECT_CALL(delegate_mock_, OnWillRetryFetchingIssuers);
  EXPECT_CALL(delegate_mock_, OnDidRetryFetchingIssuers).Times(0);
  EXPECT_CALL(delegate_mock_, OnDidFetchIssuers).Times(0);
  issuers_->PeriodicallyFetch();

  EXPECT_FALSE(GetIssuers());
}

TEST_F(CatsxpAdsIssuersTest,
       RetryAfterHttpInternalServerErrorResponseStatusCode) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildIssuersUrlPath(),
       {{net::HTTP_INTERNAL_SERVER_ERROR,
         /*response_body=*/std::string(
             net::GetHttpReasonPhrase(net::HTTP_INTERNAL_SERVER_ERROR))},
        {net::HTTP_OK, test::BuildIssuersUrlResponseBody()}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  ON_CALL(delegate_mock_, OnDidFetchIssuers)
      .WillByDefault([](const IssuersInfo& issuers) {
        // Set issuers to prevent further retries.
        SetIssuers(issuers);
      });

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnFailedToFetchIssuers);
  EXPECT_CALL(delegate_mock_, OnWillRetryFetchingIssuers);
  EXPECT_CALL(delegate_mock_, OnDidRetryFetchingIssuers);
  EXPECT_CALL(delegate_mock_, OnDidFetchIssuers);
  issuers_->PeriodicallyFetch();
  FastForwardClockToNextPendingTask();

  EXPECT_TRUE(HasIssuers());
}

TEST_F(CatsxpAdsIssuersTest, DoNotRetryAfterHttpForbiddenResponseStatusCode) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildIssuersUrlPath(),
       {{net::HTTP_FORBIDDEN,
         /*response_body=*/std::string(
             net::GetHttpReasonPhrase(net::HTTP_FORBIDDEN))},
        {net::HTTP_OK, test::BuildIssuersUrlResponseBody()}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnFailedToFetchIssuers);
  EXPECT_CALL(delegate_mock_, OnDidFetchIssuers).Times(0);
  EXPECT_CALL(delegate_mock_, OnWillRetryFetchingIssuers).Times(0);
  EXPECT_CALL(delegate_mock_, OnDidRetryFetchingIssuers).Times(0);
  EXPECT_CALL(delegate_mock_, OnDidFetchIssuers).Times(0);
  issuers_->PeriodicallyFetch();

  EXPECT_FALSE(HasPendingTasks());
}

}  // namespace catsxp_ads
