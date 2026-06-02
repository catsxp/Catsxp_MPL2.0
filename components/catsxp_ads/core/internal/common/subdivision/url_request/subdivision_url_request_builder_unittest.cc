/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/subdivision_url_request_builder.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSubdivisionUrlRequestBuilderTest : public test::TestBase {};

TEST_F(CatsxpAdsSubdivisionUrlRequestBuilderTest, BuildUrl) {
  // Arrange
  GetSubdivisionUrlRequestBuilder url_request_builder;

  // Act
  const mojom::UrlRequestInfoPtr mojom_url_request =
      url_request_builder.Build();

  // Assert
  const mojom::UrlRequestInfoPtr expected_mojom_url_request =
      mojom::UrlRequestInfo::New();
  expected_mojom_url_request->url =
      GURL("https://geo.ads.catsxpsoftware.com/v1/getstate");
  expected_mojom_url_request->method = mojom::UrlRequestMethodType::kGet;
  EXPECT_EQ(expected_mojom_url_request, mojom_url_request);
}

}  // namespace catsxp_ads
