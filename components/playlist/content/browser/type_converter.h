/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_TYPE_CONVERTER_H_
#define CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_TYPE_CONVERTER_H_

#include "base/values.h"
#include "catsxp/components/playlist/core/common/mojom/playlist.mojom.h"

namespace playlist {

bool IsItemValueMalformed(const base::DictValue& dict);

void MigratePlaylistOrder(const base::DictValue& playlists,
                          base::ListValue& order);

// Converters between mojom::PlaylistItem and base::Value --------------------
mojom::PlaylistItemPtr ConvertValueToPlaylistItem(const base::DictValue& dict);
base::DictValue ConvertPlaylistItemToValue(const mojom::PlaylistItemPtr& item);

// Converters between mojom::PlaylistItemList and base::Value ----------------
// Note that Playlist value only contains the ids of its
// children. The actual value of the children is stored in a separate value.
// This is to make playlist items can be shared by multiple playlists. For
// more details, please see a comment in playlist/pref_names.h
mojom::PlaylistPtr ConvertValueToPlaylist(const base::DictValue& playlist_dict,
                                          const base::DictValue& items_dict);
base::DictValue ConvertPlaylistToValue(const mojom::PlaylistPtr& playlist);

}  // namespace playlist

#endif  // CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_TYPE_CONVERTER_H_
