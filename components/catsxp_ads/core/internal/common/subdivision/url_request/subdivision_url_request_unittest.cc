/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/subdivision_url_request.h"

#include <memory>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/subdivision_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/test/subdivision_url_request_delegate_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/test/subdivision_url_request_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "net/http/http_status_code.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSubdivisionUrlRequestTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    subdivision_url_request_ = std::make_unique<SubdivisionUrlRequest>();
    subdivision_url_request_->SetDelegate(&delegate_mock_);
  }

  std::unique_ptr<SubdivisionUrlRequest> subdivision_url_request_;
  ::testing::NiceMock<SubdivisionUrlRequestDelegateMock> delegate_mock_;
};

TEST_F(CatsxpAdsSubdivisionUrlRequestTest,
       SchedulesPeriodicFetchAfterHttpOkResponseStatusCode) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(),
       {{net::HTTP_OK,
         test::BuildSubdivisionUrlResponseBody(/*country_code=*/"US",
                                               /*subdivision_code=*/"CA")}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act
  subdivision_url_request_->PeriodicallyFetch();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(CatsxpAdsSubdivisionUrlRequestTest,
       SchedulesRetryAfterHttpInternalServerErrorResponseStatusCode) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(),
       {{net::HTTP_INTERNAL_SERVER_ERROR,
         std::string(
             net::GetHttpReasonPhrase(net::HTTP_INTERNAL_SERVER_ERROR))}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act
  subdivision_url_request_->PeriodicallyFetch();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(CatsxpAdsSubdivisionUrlRequestTest,
       SchedulesRetryAfterHttpUnauthorizedResponseStatusCode) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(),
       {{net::HTTP_UNAUTHORIZED,
         std::string(net::GetHttpReasonPhrase(net::HTTP_UNAUTHORIZED))}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act
  subdivision_url_request_->PeriodicallyFetch();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(CatsxpAdsSubdivisionUrlRequestTest,
       DoNotRetryAfterHttpForbiddenResponseStatusCode) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(),
       {{net::HTTP_FORBIDDEN,
         std::string(net::GetHttpReasonPhrase(net::HTTP_FORBIDDEN))}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act
  subdivision_url_request_->PeriodicallyFetch();

  // Assert
  EXPECT_FALSE(HasPendingTasks());
}

TEST_F(CatsxpAdsSubdivisionUrlRequestTest,
       SchedulesRetryAfterHttpTooManyRequestsResponseStatusCode) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(),
       {{net::HTTP_TOO_MANY_REQUESTS,
         std::string(net::GetHttpReasonPhrase(net::HTTP_TOO_MANY_REQUESTS))}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act
  subdivision_url_request_->PeriodicallyFetch();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(
    CatsxpAdsSubdivisionUrlRequestTest,
    SchedulesPeriodicFetchAfterRetryingHttpInternalServerErrorResponseStatusCode) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(),
       {{net::HTTP_INTERNAL_SERVER_ERROR,
         std::string(
             net::GetHttpReasonPhrase(net::HTTP_INTERNAL_SERVER_ERROR))},
        {net::HTTP_OK,
         test::BuildSubdivisionUrlResponseBody(/*country_code=*/"US",
                                               /*subdivision_code=*/"CA")}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act
  subdivision_url_request_->PeriodicallyFetch();
  FastForwardClockToNextPendingTask();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

TEST_F(CatsxpAdsSubdivisionUrlRequestTest,
       DoNotFetchIfAlreadyPeriodicallyFetching) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(),
       {{net::HTTP_OK,
         test::BuildSubdivisionUrlResponseBody(/*country_code=*/"US",
                                               /*subdivision_code=*/"CA")}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  subdivision_url_request_->PeriodicallyFetch();
  const size_t expected_pending_task_count = GetPendingTaskCount();

  // Act
  subdivision_url_request_->PeriodicallyFetch();

  // Assert
  EXPECT_EQ(expected_pending_task_count, GetPendingTaskCount());
}

TEST_F(CatsxpAdsSubdivisionUrlRequestTest,
       SchedulesRetryAfterMalformedResponseBody) {
  // Arrange
  const test::URLResponseMap url_responses = {
      {BuildSubdivisionUrlPath(),
       {{net::HTTP_OK, /*response_body=*/"malformed"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act
  subdivision_url_request_->PeriodicallyFetch();

  // Assert
  EXPECT_TRUE(HasPendingTasks());
}

}  // namespace catsxp_ads
