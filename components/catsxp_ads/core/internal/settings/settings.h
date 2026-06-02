/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SETTINGS_SETTINGS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SETTINGS_SETTINGS_H_

namespace catsxp_ads {

bool UserHasJoinedCatsxpRewards();
bool UserHasJoinedCatsxpRewardsAndNotConnectedWallet();
bool UserHasJoinedCatsxpRewardsAndConnectedWallet();

bool UserHasOptedInToNewTabPageAds();

bool UserHasOptedInToNotificationAds();
int GetMaximumNotificationAdsPerHour();

bool UserHasOptedInToSearchResultAds();

bool UserHasOptedInToSurveyPanelist();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SETTINGS_SETTINGS_H_
