/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/catalog_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "net/http/http_status_code.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCatalogPermissionRuleIntegrationTest : public test::TestBase {
 public:
  CatsxpAdsCatalogPermissionRuleIntegrationTest()
      : test::TestBase(/*is_integration_test=*/true) {}

 protected:
  void SetUpMocks() override {
    const test::URLResponseMap url_responses = {
        {BuildCatalogUrlPath(),
         {{net::HTTP_OK, /*response_body=*/"/catalog.json"}}}};
    test::MockUrlResponses(ads_client_mock_, url_responses);
  }
};

TEST_F(CatsxpAdsCatalogPermissionRuleIntegrationTest, ShouldAllow) {
  // Act & Assert
  EXPECT_TRUE(HasCatalogPermission());
}

TEST_F(CatsxpAdsCatalogPermissionRuleIntegrationTest,
       ShouldAllowIfCatalogWasLastUpdated23HoursAnd59MinutesAgo) {
  // Arrange
  AdvanceClockBy(base::Days(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_TRUE(HasCatalogPermission());
}

TEST_F(CatsxpAdsCatalogPermissionRuleIntegrationTest,
       ShouldNotAllowIfCatalogWasLastUpdated1DayAgo) {
  // Arrange
  AdvanceClockBy(base::Days(1));

  // Act & Assert
  EXPECT_FALSE(HasCatalogPermission());
}

TEST_F(CatsxpAdsCatalogPermissionRuleIntegrationTest,
       ShouldNotAllowIfCatalogDoesNotExist) {
  // Arrange
  SetCatalogVersion(0);

  // Act & Assert
  EXPECT_FALSE(HasCatalogPermission());
}

}  // namespace catsxp_ads
