/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_PREFS_PREF_PATH_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_PREFS_PREF_PATH_UTIL_H_

#include <string_view>

namespace catsxp_ads {

bool DoesMatchUserHasJoinedCatsxpRewardsPrefPath(std::string_view path);

bool DoesMatchUserHasOptedInToNewTabPageAdsPrefPath(std::string_view path);

bool DoesMatchUserHasOptedInToNotificationAdsPrefPath(std::string_view path);

bool DoesMatchUserHasOptedInToSearchResultAdsPrefPath(std::string_view path);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_PREFS_PREF_PATH_UTIL_H_
