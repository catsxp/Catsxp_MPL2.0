/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/deposits/cash_deposit.h"

#include "base/test/run_until.h"
#include "base/test/test_future.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "net/http/http_status_code.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCashDepositIntegrationTest : public test::TestBase {
 public:
  CatsxpAdsCashDepositIntegrationTest()
      : test::TestBase(/*is_integration_test=*/true) {}

 protected:
  void SetUpMocks() override {
    const test::URLResponseMap url_responses = {
        {BuildCatalogUrlPath(),
         {{net::HTTP_OK, /*response_body=*/"/catalog.json"}}}};
    test::MockUrlResponses(ads_client_mock_, url_responses);
  }
};

TEST_F(CatsxpAdsCashDepositIntegrationTest, GetValue) {
  // Arrange
  CashDeposit deposit;

  // Act & Assert
  ASSERT_TRUE(base::test::RunUntil([&] {
    base::test::TestFuture<bool, double> test_future;
    deposit.GetValue(test::kCreativeInstanceId, test_future.GetCallback());
    const auto [success, value] = test_future.Take();
    if (!success) {
      return false;
    }
    EXPECT_DOUBLE_EQ(test::kValue, value);
    return true;
  }));
}

TEST_F(CatsxpAdsCashDepositIntegrationTest,
       DoNotGetValueForMissingCreativeInstanceId) {
  // Arrange
  CashDeposit deposit;

  // Act & Assert
  base::test::TestFuture<bool, double> test_future;
  deposit.GetValue(test::kMissingCreativeInstanceId, test_future.GetCallback());
  const auto [success, value] = test_future.Take();
  EXPECT_FALSE(success);
  EXPECT_DOUBLE_EQ(0.0, value);
}

}  // namespace catsxp_ads
