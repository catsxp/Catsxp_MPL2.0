/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_idle_detection/user_idle_detection_util.h"

#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/public/user_attention/user_idle_detection/user_idle_detection_feature.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsUserIdleDetectionUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsUserIdleDetectionUtilTest, WasLocked) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature, {{"should_detect_screen_was_locked", "true"}});

  // Act & Assert
  EXPECT_TRUE(MaybeScreenWasLocked(/*screen_was_locked=*/true));
}

TEST_F(CatsxpAdsUserIdleDetectionUtilTest,
       WasLockedIfShouldDetectScreenWasLocked) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature, {{"should_detect_screen_was_locked", "true"}});

  // Act & Assert
  EXPECT_TRUE(MaybeScreenWasLocked(/*screen_was_locked=*/true));
}

TEST_F(CatsxpAdsUserIdleDetectionUtilTest, WasNotLocked) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature, {{"should_detect_screen_was_locked", "true"}});

  // Act & Assert
  EXPECT_FALSE(MaybeScreenWasLocked(/*screen_was_locked=*/false));
}

TEST_F(CatsxpAdsUserIdleDetectionUtilTest,
       WasNotLockedIfShouldNotDetectWasLocked) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature,
      {{"should_detect_screen_was_locked", "false"}});

  // Act & Assert
  EXPECT_FALSE(MaybeScreenWasLocked(/*screen_was_locked=*/true));
}

TEST_F(CatsxpAdsUserIdleDetectionUtilTest, HasNotExceededMaximumIdleTime) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature, {{"maximum_idle_time", "10s"}});

  // Act & Assert
  EXPECT_FALSE(HasExceededMaximumIdleTime(base::Seconds(10)));
}

TEST_F(CatsxpAdsUserIdleDetectionUtilTest,
       HasNotExceededInfiniteMaximumIdleTime) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature, {{"maximum_idle_time", "0s"}});

  // Act & Assert
  EXPECT_FALSE(HasExceededMaximumIdleTime(base::TimeDelta::Max()));
}

TEST_F(CatsxpAdsUserIdleDetectionUtilTest, HasExceededMaximumIdleTime) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature, {{"maximum_idle_time", "10s"}});

  // Act & Assert
  EXPECT_TRUE(HasExceededMaximumIdleTime(base::Seconds(11)));
}

}  // namespace catsxp_ads
