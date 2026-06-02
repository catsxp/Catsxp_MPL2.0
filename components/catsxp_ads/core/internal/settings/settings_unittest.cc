/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_feature.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsSettingsTest : public test::TestBase {};

TEST_F(CatsxpAdsSettingsTest, UserHasJoinedCatsxpRewards) {
  // Act & Assert
  EXPECT_TRUE(UserHasJoinedCatsxpRewards());
}

TEST_F(CatsxpAdsSettingsTest, UserHasNotJoinedCatsxpRewards) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  EXPECT_FALSE(UserHasJoinedCatsxpRewards());
}

TEST_F(CatsxpAdsSettingsTest, UserHasJoinedCatsxpRewardsAndConnectedWallet) {
  // Act & Assert
  EXPECT_TRUE(UserHasJoinedCatsxpRewardsAndConnectedWallet());
  EXPECT_FALSE(UserHasJoinedCatsxpRewardsAndNotConnectedWallet());
}

TEST_F(CatsxpAdsSettingsTest, UserHasJoinedCatsxpRewardsAndNotConnectedWallet) {
  // Arrange
  test::DisconnectExternalCatsxpRewardsWallet();

  // Act & Assert
  EXPECT_FALSE(UserHasJoinedCatsxpRewardsAndConnectedWallet());
  EXPECT_TRUE(UserHasJoinedCatsxpRewardsAndNotConnectedWallet());
}

TEST_F(CatsxpAdsSettingsTest, UserHasOptedInToNewTabPageAds) {
  // Act & Assert
  EXPECT_TRUE(UserHasOptedInToNewTabPageAds());
}

TEST_F(CatsxpAdsSettingsTest, UserHasNotOptedInToNewTabPageAds) {
  // Arrange
  test::OptOutOfNewTabPageAds();

  // Act & Assert
  EXPECT_FALSE(UserHasOptedInToNewTabPageAds());
}

TEST_F(CatsxpAdsSettingsTest, UserHasOptedInToNotificationAds) {
  // Act & Assert
  EXPECT_TRUE(UserHasOptedInToNotificationAds());
}

TEST_F(CatsxpAdsSettingsTest, UserHasNotOptedInToNotificationAds) {
  // Arrange
  test::OptOutOfNotificationAds();

  // Act & Assert
  EXPECT_FALSE(UserHasOptedInToNotificationAds());
}

TEST_F(CatsxpAdsSettingsTest, MaximumNotificationAdsPerHour) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kNotificationAdFeature, {{"default_ads_per_hour", "2"}});

  test::SetProfileInt64PrefValue(prefs::kMaximumNotificationAdsPerHour, 3);

  // Act & Assert
  EXPECT_EQ(3, GetMaximumNotificationAdsPerHour());
}

TEST_F(CatsxpAdsSettingsTest, DefaultMaximumNotificationAdsPerHour) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kNotificationAdFeature, {{"default_ads_per_hour", "2"}});

  // Act & Assert
  EXPECT_EQ(2, GetMaximumNotificationAdsPerHour());
}

TEST_F(CatsxpAdsSettingsTest, UserHasOptedInToSearchResultAds) {
  // Act & Assert
  EXPECT_TRUE(UserHasOptedInToSearchResultAds());
}

TEST_F(CatsxpAdsSettingsTest, UserHasNotOptedInToSearchResultAds) {
  // Arrange
  test::OptOutOfSearchResultAds();

  // Act & Assert
  EXPECT_FALSE(UserHasOptedInToSearchResultAds());
}

}  // namespace catsxp_ads
