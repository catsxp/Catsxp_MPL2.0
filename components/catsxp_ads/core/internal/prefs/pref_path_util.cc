/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_path_util.h"

#include <string_view>

#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "catsxp/components/catsxp_rewards/core/pref_names.h"
#include "catsxp/components/ntp_background_images/common/pref_names.h"

namespace catsxp_ads {

bool DoesMatchUserHasJoinedCatsxpRewardsPrefPath(std::string_view path) {
  return path == catsxp_rewards::prefs::kEnabled;
}

bool DoesMatchUserHasOptedInToNewTabPageAdsPrefPath(std::string_view path) {
  return path == ntp_background_images::prefs::kNewTabPageShowBackgroundImage ||
         path == ntp_background_images::prefs::
                     kNewTabPageShowSponsoredImagesBackgroundImage;
}

bool DoesMatchUserHasOptedInToNotificationAdsPrefPath(std::string_view path) {
  return path == prefs::kOptedInToNotificationAds;
}

bool DoesMatchUserHasOptedInToSearchResultAdsPrefPath(std::string_view path) {
  return path == prefs::kOptedInToSearchResultAds;
}

}  // namespace catsxp_ads
