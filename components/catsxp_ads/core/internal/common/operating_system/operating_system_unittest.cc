/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system.h"

#include "catsxp/components/catsxp_ads/core/internal/common/operating_system/operating_system_types.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsOperatingSystemTest : public test::TestBase {};

TEST_F(CatsxpAdsOperatingSystemTest, GetNameForAndroid) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kAndroid);

  // Act & Assert
  EXPECT_EQ("android", OperatingSystem::GetInstance().GetName());
}

TEST_F(CatsxpAdsOperatingSystemTest, GetNameForIOS) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kIOS);

  // Act & Assert
  EXPECT_EQ("ios", OperatingSystem::GetInstance().GetName());
}

TEST_F(CatsxpAdsOperatingSystemTest, GetNameForLinux) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kLinux);

  // Act & Assert
  EXPECT_EQ("linux", OperatingSystem::GetInstance().GetName());
}

TEST_F(CatsxpAdsOperatingSystemTest, GetNameForMacOS) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kMacOS);

  // Act & Assert
  EXPECT_EQ("macos", OperatingSystem::GetInstance().GetName());
}

TEST_F(CatsxpAdsOperatingSystemTest, GetNameForWindows) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kWindows);

  // Act & Assert
  EXPECT_EQ("windows", OperatingSystem::GetInstance().GetName());
}

TEST_F(CatsxpAdsOperatingSystemTest, GetTypeForAndroid) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kAndroid);

  // Act & Assert
  EXPECT_EQ(OperatingSystemType::kAndroid,
            OperatingSystem::GetInstance().GetType());
}

TEST_F(CatsxpAdsOperatingSystemTest, GetTypeForIOS) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kIOS);

  // Act & Assert
  EXPECT_EQ(OperatingSystemType::kIOS,
            OperatingSystem::GetInstance().GetType());
}

TEST_F(CatsxpAdsOperatingSystemTest, GetTypeForLinux) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kLinux);

  // Act & Assert
  EXPECT_EQ(OperatingSystemType::kLinux,
            OperatingSystem::GetInstance().GetType());
}

TEST_F(CatsxpAdsOperatingSystemTest, GetTypeForMacOS) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kMacOS);

  // Act & Assert
  EXPECT_EQ(OperatingSystemType::kMacOS,
            OperatingSystem::GetInstance().GetType());
}

TEST_F(CatsxpAdsOperatingSystemTest, GetTypeForWindows) {
  // Arrange
  fake_operating_system_.SetType(OperatingSystemType::kWindows);

  // Act & Assert
  EXPECT_EQ(OperatingSystemType::kWindows,
            OperatingSystem::GetInstance().GetType());
}

}  // namespace catsxp_ads
