/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_version.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAdsBrowserVersion*

namespace catsxp_ads {

class CatsxpAdsBrowserVersionTest : public test::TestBase {};

TEST_F(CatsxpAdsBrowserVersionTest, GetNumberAfterSetNumber) {
  // Arrange
  fake_browser_version_.SetNumber("1.33.7.42");

  // Act & Assert
  EXPECT_EQ("1.33.7.42", BrowserVersion::GetInstance().GetNumber());
}

}  // namespace catsxp_ads
