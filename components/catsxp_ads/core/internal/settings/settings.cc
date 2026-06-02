/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/notification_ad/notification_ad_feature.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "catsxp/components/catsxp_rewards/core/pref_names.h"
#include "catsxp/components/ntp_background_images/common/pref_names.h"

namespace catsxp_ads {

namespace {

bool HasConnectedWallet() {
  return !GetProfileStringPref(catsxp_rewards::prefs::kExternalWalletType)
              .empty();
}

}  // namespace

bool UserHasJoinedCatsxpRewards() {
  return GetProfileBooleanPref(catsxp_rewards::prefs::kEnabled);
}

bool UserHasJoinedCatsxpRewardsAndNotConnectedWallet() {
  return UserHasJoinedCatsxpRewards() && !HasConnectedWallet();
}

bool UserHasJoinedCatsxpRewardsAndConnectedWallet() {
  return UserHasJoinedCatsxpRewards() && HasConnectedWallet();
}

bool UserHasOptedInToNewTabPageAds() {
  return GetProfileBooleanPref(
             ntp_background_images::prefs::kNewTabPageShowBackgroundImage) &&
         GetProfileBooleanPref(
             ntp_background_images::prefs::
                 kNewTabPageShowSponsoredImagesBackgroundImage);
}

bool UserHasOptedInToNotificationAds() {
  return UserHasJoinedCatsxpRewards() &&
         GetProfileBooleanPref(prefs::kOptedInToNotificationAds);
}

int GetMaximumNotificationAdsPerHour() {
  const int ads_per_hour = static_cast<int>(
      GetProfileInt64Pref(prefs::kMaximumNotificationAdsPerHour));

  return ads_per_hour > 0 ? ads_per_hour : kDefaultNotificationAdsPerHour.Get();
}

bool UserHasOptedInToSearchResultAds() {
  return GetProfileBooleanPref(prefs::kOptedInToSearchResultAds);
}

bool UserHasOptedInToSurveyPanelist() {
  if (GetProfileBooleanPref(catsxp_rewards::prefs::kDisabledByPolicy)) {
    return false;
  }
  return GetProfileBooleanPref(
      ntp_background_images::prefs::kNewTabPageSponsoredImagesSurveyPanelist);
}

}  // namespace catsxp_ads
