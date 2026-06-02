/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "catsxp/components/catsxp_rewards/core/pref_names.h"
#include "catsxp/components/ntp_background_images/common/pref_names.h"

namespace catsxp_ads::test {

void DisableCatsxpRewards() {
  SetProfileBooleanPrefValue(catsxp_rewards::prefs::kEnabled, false);
  DisconnectExternalCatsxpRewardsWallet();
}

void DisconnectExternalCatsxpRewardsWallet() {
  SetProfileStringPrefValue(catsxp_rewards::prefs::kExternalWalletType, "");
}

void OptOutOfNewTabPageAds() {
  SetProfileBooleanPrefValue(
      ntp_background_images::prefs::kNewTabPageShowBackgroundImage, false);
  SetProfileBooleanPrefValue(ntp_background_images::prefs::
                                 kNewTabPageShowSponsoredImagesBackgroundImage,
                             false);
}

void OptOutOfNotificationAds() {
  SetProfileBooleanPrefValue(prefs::kOptedInToNotificationAds, false);
}

void SetMaximumNotificationAdsPerHour(int max_ads_per_hour) {
  SetProfileInt64PrefValue(prefs::kMaximumNotificationAdsPerHour,
                           max_ads_per_hour);
}

void OptOutOfSearchResultAds() {
  SetProfileBooleanPrefValue(prefs::kOptedInToSearchResultAds, false);
}

void OptOutOfAllAds() {
  OptOutOfNewTabPageAds();
  OptOutOfNotificationAds();
  OptOutOfSearchResultAds();
}

void OptOutOfSurveyPanelist() {
  SetProfileBooleanPrefValue(
      ntp_background_images::prefs::kNewTabPageSponsoredImagesSurveyPanelist,
      false);
}

}  // namespace catsxp_ads::test
