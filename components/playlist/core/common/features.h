/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_PLAYLIST_CORE_COMMON_FEATURES_H_
#define CATSXP_COMPONENTS_PLAYLIST_CORE_COMMON_FEATURES_H_

#include "base/feature_list.h"
#include "catsxp/components/playlist/core/common/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_PLAYLIST));

namespace playlist::features {

BASE_DECLARE_FEATURE(kPlaylist);

BASE_DECLARE_FEATURE(kPlaylistFakeUA);

}  // namespace playlist::features

#endif  // CATSXP_COMPONENTS_PLAYLIST_CORE_COMMON_FEATURES_H_
