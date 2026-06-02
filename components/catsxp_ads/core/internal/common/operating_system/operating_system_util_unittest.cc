/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system.h"
#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_types.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsOperatingSystemUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsOperatingSystemUtilTest, IsMobileOnAndroid) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kAndroid);
  OperatingSystem::SetForTesting(&fake_operating_system_);

  // Act & Assert
  EXPECT_TRUE(IsMobile());
}

TEST_F(CatsxpAdsOperatingSystemUtilTest, IsMobileOnIOS) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kIOS);
  OperatingSystem::SetForTesting(&fake_operating_system_);

  // Act & Assert
  EXPECT_TRUE(IsMobile());
}

TEST_F(CatsxpAdsOperatingSystemUtilTest, IsNotMobileOnLinux) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kLinux);
  OperatingSystem::SetForTesting(&fake_operating_system_);

  // Act & Assert
  EXPECT_FALSE(IsMobile());
}

TEST_F(CatsxpAdsOperatingSystemUtilTest, IsNotMobileOnMacOS) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kMacOS);
  OperatingSystem::SetForTesting(&fake_operating_system_);

  // Act & Assert
  EXPECT_FALSE(IsMobile());
}

TEST_F(CatsxpAdsOperatingSystemUtilTest, IsNotMobileOnWindows) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kWindows);
  OperatingSystem::SetForTesting(&fake_operating_system_);

  // Act & Assert
  EXPECT_FALSE(IsMobile());
}

}  // namespace catsxp_ads
