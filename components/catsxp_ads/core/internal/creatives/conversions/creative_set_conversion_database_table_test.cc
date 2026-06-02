/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_database_table.h"

#include "base/test/run_until.h"
#include "base/test/test_future.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "net/http/http_status_code.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConversionsDatabaseTableIntegrationTest : public test::TestBase {
 public:
  CatsxpAdsConversionsDatabaseTableIntegrationTest()
      : test::TestBase(/*is_integration_test=*/true) {}

 protected:
  void SetUpMocks() override {
    const test::URLResponseMap url_responses = {
        {BuildCatalogUrlPath(),
         {{net::HTTP_OK, /*response_body=*/"/catalog.json"}}}};
    test::MockUrlResponses(ads_client_mock_, url_responses);
  }
};

TEST_F(CatsxpAdsConversionsDatabaseTableIntegrationTest,
       GetConversionsFromCatalogResponse) {
  // Arrange
  const database::table::CreativeSetConversions database_table;

  // Act & Assert
  ASSERT_TRUE(base::test::RunUntil([&] {
    base::test::TestFuture<bool, CreativeSetConversionList> test_future;
    database_table.GetUnexpired(
        test_future.GetCallback<bool, const CreativeSetConversionList&>());
    const auto [success, creative_set_conversions] = test_future.Take();
    if (!success || creative_set_conversions.empty()) {
      return false;
    }
    EXPECT_THAT(creative_set_conversions, ::testing::SizeIs(2));
    return true;
  }));
}

}  // namespace catsxp_ads
