/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/page_land_user_data.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "net/http/http_status_code.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsPageLandUserDataTest : public test::TestBase {};

TEST_F(CatsxpAdsPageLandUserDataTest,
       BuildPageLandUserDataForHttpInformationalResponseStatusCodeClass) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "1xx"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_SWITCHING_PROTOCOLS));
}

TEST_F(CatsxpAdsPageLandUserDataTest,
       BuildPageLandUserDataForHttpSuccessfulResponseStatusCodeClass) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "2xx"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_IM_USED));
}

TEST_F(CatsxpAdsPageLandUserDataTest,
       BuildPageLandUserDataForHttpRedirectionMessageStatusCodeClass) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "3xx"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_MOVED_PERMANENTLY));
}

TEST_F(CatsxpAdsPageLandUserDataTest,
       BuildPageLandUserDataForHttpClientErrorResponseStatusCode) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "404"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_NOT_FOUND));
}

TEST_F(CatsxpAdsPageLandUserDataTest,
       BuildPageLandUserDataForHttpClientErrorResponseStatusCodeClass) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "4xx"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_UPGRADE_REQUIRED));
}

TEST_F(
    CatsxpAdsPageLandUserDataTest,
    BuildPageLandUserDataForPrivacyPreservingHttpServerErrorResponseStatusCode) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "500"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_INTERNAL_SERVER_ERROR));
}

TEST_F(
    CatsxpAdsPageLandUserDataTest,
    BuildPageLandUserDataForPrivacyPreservingHttpServerErrorResponseStatusCodeClass) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "5xx"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_LOOP_DETECTED));
}

TEST_F(
    CatsxpAdsPageLandUserDataTest,
    DoNotBuildPageLandUserDataForHttpResponseStatusErrorPageForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_THAT(BuildPageLandUserData(net::HTTP_NOT_FOUND), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
