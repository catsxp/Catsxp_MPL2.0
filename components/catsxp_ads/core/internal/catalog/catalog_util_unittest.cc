/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_util.h"

#include "base/test/test_future.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/test/catalog_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsCatalogUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsCatalogUtilTest, ResetCatalog) {
  // Arrange
  SetCatalogId(test::kCatalogId);
  SetCatalogVersion(1);
  SetCatalogPing(base::Hours(1));
  SetCatalogLastUpdated(test::Now());

  // Act
  base::test::TestFuture<bool> test_future;
  ResetCatalog(test_future.GetCallback());
  ASSERT_TRUE(test_future.Get());

  // Assert
  EXPECT_THAT(GetProfileStringPref(prefs::kCatalogId), ::testing::IsEmpty());
  EXPECT_EQ(0, GetProfileIntegerPref(prefs::kCatalogVersion));
  EXPECT_EQ(7'200'000, GetProfileInt64Pref(prefs::kCatalogPing));
  EXPECT_TRUE(GetProfileTimePref(prefs::kCatalogLastUpdated).is_null());
}

TEST_F(CatsxpAdsCatalogUtilTest, CatalogExists) {
  // Arrange
  SetCatalogVersion(1);

  // Act & Assert
  EXPECT_TRUE(DoesCatalogExist());
}

TEST_F(CatsxpAdsCatalogUtilTest, CatalogDoesNotExist) {
  // Arrange
  SetCatalogVersion(0);

  // Act & Assert
  EXPECT_FALSE(DoesCatalogExist());
}

TEST_F(CatsxpAdsCatalogUtilTest, CatalogHasChanged) {
  // Arrange
  SetCatalogId(test::kCatalogId);

  // Act & Assert
  EXPECT_TRUE(HasCatalogChanged(
      /*catalog_id=*/"150a9518-4db8-4fba-b104-0c420a1d9c0c"));
}

TEST_F(CatsxpAdsCatalogUtilTest, CatalogHasNotChanged) {
  // Arrange
  SetCatalogId(test::kCatalogId);

  // Act & Assert
  EXPECT_FALSE(HasCatalogChanged(test::kCatalogId));
}

TEST_F(CatsxpAdsCatalogUtilTest, CatalogHasExpired) {
  // Arrange
  SetCatalogLastUpdated(test::Now());

  AdvanceClockBy(base::Days(1));

  // Act & Assert
  EXPECT_TRUE(HasCatalogExpired());
}

TEST_F(CatsxpAdsCatalogUtilTest, CatalogHasNotExpired) {
  // Arrange
  SetCatalogLastUpdated(test::Now());

  AdvanceClockBy(base::Days(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_FALSE(HasCatalogExpired());
}

}  // namespace catsxp_ads
