/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_util.h"

#include "catsxp/components/catsxp_ads/core/internal/application_state/test/fake_browser_version.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAdsBrowserUtil*

namespace catsxp_ads {

class CatsxpAdsBrowserUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsBrowserUtilTest, BrowserWasNotUpgradedWhenVersionHasNotChanged) {
  // Arrange
  fake_browser_version_.SetNumber(test::kDefaultBrowserVersionNumber);
  test::SetProfileStringPrefValue(prefs::kBrowserVersionNumber,
                                  test::kDefaultBrowserVersionNumber);

  // Act & Assert
  EXPECT_FALSE(WasBrowserUpgraded());
}

TEST_F(CatsxpAdsBrowserUtilTest, BrowserWasUpgradedWhenVersionChanges) {
  // Arrange
  test::SetProfileStringPrefValue(prefs::kBrowserVersionNumber, "1.0.0.0");
  fake_browser_version_.SetNumber("1.33.7.42");

  // Act
  EXPECT_TRUE(WasBrowserUpgraded());

  // Assert
  EXPECT_EQ("1.33.7.42", GetProfileStringPref(prefs::kBrowserVersionNumber));
}

}  // namespace catsxp_ads
