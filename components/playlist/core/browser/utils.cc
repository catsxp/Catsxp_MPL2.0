/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/playlist/core/browser/utils.h"

#include "base/check.h"
#include "base/feature_list.h"
#include "catsxp/components/playlist/core/common/features.h"
#include "catsxp/components/playlist/core/common/pref_names.h"
#include "components/prefs/pref_service.h"

namespace playlist {

namespace {

bool IsDisabledByPolicy(PrefService* prefs) {
  return prefs->IsManagedPreference(kPlaylistEnabledPref) &&
         !prefs->GetBoolean(kPlaylistEnabledPref);
}

}  // namespace

bool IsPlaylistAllowed(PrefService* prefs) {
  DCHECK(prefs);
  return base::FeatureList::IsEnabled(features::kPlaylist) &&
         !IsDisabledByPolicy(prefs);
}

}  // namespace playlist
