/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_PLAYLIST_CORE_COMMON_PREF_NAMES_H_
#define CATSXP_COMPONENTS_PLAYLIST_CORE_COMMON_PREF_NAMES_H_

#include "catsxp/components/playlist/core/common/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_PLAYLIST));

namespace playlist {

// A boolean preference indicates whether playlist feature is enabled or not by
// the user.
inline constexpr char kPlaylistEnabledPref[] = "catsxp.playlist.enabled";

// Set of playlists. Each playlist has ids of its items
// so that playlists can share same item efficiently
// Currently, List type preference always has to be updated entirely but there
// are many cases where we only need update small part of it.
// Thus, in order to update playlists efficiently, this pref is in Dictionary
//
// e.g. {
//        "list1": {name: "playlist1", items: [id1, id2, id3]},
//        "list2": {name: "playlist2", items: [id1, id4, id5] }
//      }                                       ^ same item
inline constexpr char kPlaylistsPref[] = "catsxp.playlist.lists";

// Stores order of playlists.
// ["id1", "id2" ... ]
inline constexpr char kPlaylistOrderPref[] = "catsxp.playlist.lists_order";

// Stores playlist item key-value pairs in a dict. Each item has unique key and
// it's metadata(such as, title, media file path and etc..).
inline constexpr char kPlaylistItemsPref[] = "catsxp.playlist.items";

// Boolean pref indicates that we should cache media file when adding items.
inline constexpr char kPlaylistCacheByDefault[] = "catsxp.playlist.cache";

// A string indicates to which playlist items should be added by default.
inline constexpr char kPlaylistDefaultSaveTargetListID[] =
    "catsxp.playlist.default_save_target_list_id";

// Timestamp indicating first usage of playlist
inline constexpr char kPlaylistFirstUsageTime[] =
    "catsxp.playlist.first_usage_time";

// Timestamp indicating last usage of playlist
inline constexpr char kPlaylistLastUsageTime[] =
    "catsxp.playlist.last_usage_time";

// Boolean indicating if playlist was used on second day
// on first week of usage
inline constexpr char kPlaylistUsedSecondDay[] =
    "catsxp.playlist.used_second_day";

// Weekly storage event list counting usages of playlist
inline constexpr char kPlaylistUsageWeeklyStorage[] =
    "catsxp.playlist.usage_weekly_storage";

}  // namespace playlist

#endif  // CATSXP_COMPONENTS_PLAYLIST_CORE_COMMON_PREF_NAMES_H_
