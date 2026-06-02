/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/common/locale/locale_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/locale/test/fake_locale.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsLocaleUtilTest, CurrentLanguageCode) {
  // Arrange
  test::FakeLocale fake_locale;
  fake_locale.SetLanguageCode("en");

  // Act & Assert
  EXPECT_EQ("en", CurrentLanguageCode());
}

TEST(CatsxpAdsLocaleUtilTest, CurrentCountryCode) {
  // Arrange
  test::FakeLocale fake_locale;
  fake_locale.SetCountryCode("KY");

  // Act & Assert
  EXPECT_EQ("KY", CurrentCountryCode());
}

}  // namespace catsxp_ads
