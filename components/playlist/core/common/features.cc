/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/playlist/core/common/features.h"

#include "base/feature_list.h"

namespace playlist::features {

BASE_FEATURE(kPlaylist, base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kPlaylistFakeUA,
             base::FEATURE_DISABLED_BY_DEFAULT);

}  // namespace playlist::features
