/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_PLAYLIST_CORE_COMMON_PLAYLIST_RENDER_FRAME_OBSERVER_HELPER_H_
#define CATSXP_COMPONENTS_PLAYLIST_CORE_COMMON_PLAYLIST_RENDER_FRAME_OBSERVER_HELPER_H_

#include <vector>

#include "base/values.h"
#include "catsxp/components/playlist/core/common/mojom/playlist.mojom.h"

class GURL;

namespace playlist {

std::vector<mojom::PlaylistItemPtr> ExtractPlaylistItems(const GURL& url,
                                                         base::ListValue list);

}  // namespace playlist

#endif  // CATSXP_COMPONENTS_PLAYLIST_CORE_COMMON_PLAYLIST_RENDER_FRAME_OBSERVER_HELPER_H_
