/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "base/test/test_future.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/public/ads.h"

// npm run test -- catsxp_all_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsImplTest : public test::TestBase {
 public:
  CatsxpAdsImplTest() : test::TestBase(/*is_integration_test=*/true) {}
};

TEST_F(CatsxpAdsImplTest, DoesNotInitializeWhenAlreadyInitialized) {
  // Act & Assert
  base::test::TestFuture<bool> test_future;
  GetAds().Initialize(/*mojom_wallet=*/nullptr, test_future.GetCallback());
  EXPECT_FALSE(test_future.Get());
}

TEST_F(CatsxpAdsImplTest, Shutdown) {
  // Act & Assert
  base::test::TestFuture<bool> test_future;
  GetAds().Shutdown(test_future.GetCallback());
  EXPECT_TRUE(test_future.Get());
}

TEST_F(CatsxpAdsImplTest, DoesNotShutdownWhenNotInitialized) {
  // Arrange
  base::test::TestFuture<bool> shutdown_future;
  GetAds().Shutdown(shutdown_future.GetCallback());
  ASSERT_TRUE(shutdown_future.Get());

  // Act & Assert
  base::test::TestFuture<bool> test_future;
  GetAds().Shutdown(test_future.GetCallback());
  EXPECT_FALSE(test_future.Get());
}

}  // namespace catsxp_ads
