/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/browser/network/oblivious_http_client_impl.h"

#include <utility>

#include "base/test/test_future.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "net/base/net_errors.h"
#include "net/http/http_response_headers.h"
#include "net/http/http_status_code.h"
#include "services/network/public/mojom/oblivious_http_request.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {
constexpr char kUrl[] = "https://example.com/resource";
}  // namespace

class CatsxpAdsObliviousHttpClientImplTest : public testing::Test {};

TEST_F(CatsxpAdsObliviousHttpClientImplTest, OnCompletedWithNetError) {
  // Arrange
  base::test::TestFuture<mojom::UrlResponseInfoPtr> test_future;
  ObliviousHttpClientImpl oblivious_http_client_impl(GURL(kUrl),
                                                     test_future.GetCallback());

  // Act
  oblivious_http_client_impl.OnCompleted(
      network::mojom::ObliviousHttpCompletionResult::NewNetError(
          net::ERR_FAILED));

  // Assert
  EXPECT_THAT(test_future.Take(),
              ::testing::Pointee(::testing::FieldsAre(
                  GURL(kUrl), net::ERR_FAILED, /*body=*/::testing::IsEmpty(),
                  /*headers=*/::testing::IsEmpty())));
}

TEST_F(CatsxpAdsObliviousHttpClientImplTest,
       OnCompletedWithOuterResponseErrorCode) {
  // Arrange
  base::test::TestFuture<mojom::UrlResponseInfoPtr> test_future;
  ObliviousHttpClientImpl oblivious_http_client_impl(GURL(kUrl),
                                                     test_future.GetCallback());

  // Act
  oblivious_http_client_impl.OnCompleted(
      network::mojom::ObliviousHttpCompletionResult::NewOuterResponseErrorCode(
          net::HTTP_UNPROCESSABLE_CONTENT));

  // Assert
  EXPECT_THAT(
      test_future.Take(),
      ::testing::Pointee(::testing::FieldsAre(
          GURL(kUrl), net::HTTP_UNPROCESSABLE_CONTENT,
          /*body=*/::testing::IsEmpty(), /*headers=*/::testing::IsEmpty())));
}

TEST_F(CatsxpAdsObliviousHttpClientImplTest,
       OnCompletedWithInnerResponseSetsCodeAndBody) {
  // Arrange
  base::test::TestFuture<mojom::UrlResponseInfoPtr> test_future;
  ObliviousHttpClientImpl oblivious_http_client_impl(GURL(kUrl),
                                                     test_future.GetCallback());

  auto inner_response = network::mojom::ObliviousHttpResponse::New();
  inner_response->response_code = net::HTTP_OK;
  inner_response->headers =
      base::MakeRefCounted<net::HttpResponseHeaders>("HTTP/1.1 200 OK\n\n");
  inner_response->response_body = "response body";

  // Act
  oblivious_http_client_impl.OnCompleted(
      network::mojom::ObliviousHttpCompletionResult::NewInnerResponse(
          std::move(inner_response)));

  // Assert
  EXPECT_THAT(test_future.Take(), ::testing::Pointee(::testing::FieldsAre(
                                      GURL(kUrl), net::HTTP_OK, "response body",
                                      /*headers=*/::testing::IsEmpty())));
}

TEST_F(CatsxpAdsObliviousHttpClientImplTest,
       OnCompletedWithInnerResponseErrorHasEmptyBody) {
  // Arrange
  base::test::TestFuture<mojom::UrlResponseInfoPtr> test_future;
  ObliviousHttpClientImpl oblivious_http_client_impl(GURL(kUrl),
                                                     test_future.GetCallback());

  auto inner_response = network::mojom::ObliviousHttpResponse::New();
  inner_response->response_code = net::HTTP_INTERNAL_SERVER_ERROR;
  inner_response->headers = base::MakeRefCounted<net::HttpResponseHeaders>(
      "HTTP/1.1 500 Internal Server Error\n\n");
  inner_response->response_body = "";

  // Act
  oblivious_http_client_impl.OnCompleted(
      network::mojom::ObliviousHttpCompletionResult::NewInnerResponse(
          std::move(inner_response)));

  // Assert
  EXPECT_THAT(
      test_future.Take(),
      ::testing::Pointee(::testing::FieldsAre(
          GURL(kUrl), net::HTTP_INTERNAL_SERVER_ERROR,
          /*body=*/::testing::IsEmpty(), /*headers=*/::testing::IsEmpty())));
}

}  // namespace catsxp_ads
