/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_PLAYLIST_CORE_BROWSER_UTILS_H_
#define CATSXP_COMPONENTS_PLAYLIST_CORE_BROWSER_UTILS_H_

#include "catsxp/components/playlist/core/common/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_PLAYLIST));

class PrefService;

namespace playlist {

// Returns true when the Playlist feature flag is enabled and the feature has
// not been disabled by administrator policy (CatsxpPlaylistEnabled managed and
// forced off). A user toggling the pref off via settings does not count as
// "disabled by policy" -- UI remains reachable so the user can flip it back.
bool IsPlaylistAllowed(PrefService* prefs);

}  // namespace playlist

#endif  // CATSXP_COMPONENTS_PLAYLIST_CORE_BROWSER_UTILS_H_
