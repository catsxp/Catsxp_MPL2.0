/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SETTINGS_TEST_SETTINGS_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SETTINGS_TEST_SETTINGS_TEST_UTIL_H_

namespace catsxp_ads::test {

void DisableCatsxpRewards();
void DisconnectExternalCatsxpRewardsWallet();

void OptOutOfNewTabPageAds();

void OptOutOfNotificationAds();
void SetMaximumNotificationAdsPerHour(int max_ads_per_hour);

void OptOutOfSearchResultAds();

void OptOutOfAllAds();

void OptOutOfSurveyPanelist();

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SETTINGS_TEST_SETTINGS_TEST_UTIL_H_
