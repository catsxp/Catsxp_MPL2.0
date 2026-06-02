/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_PLAYLIST_TAB_HELPER_OBSERVER_H_
#define CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_PLAYLIST_TAB_HELPER_OBSERVER_H_

#include <vector>

#include "base/observer_list_types.h"
#include "catsxp/components/playlist/core/common/mojom/playlist.mojom.h"

namespace playlist {

class PlaylistTabHelperObserver : public base::CheckedObserver {
 public:
  virtual void PlaylistTabHelperWillBeDestroyed() = 0;
  virtual void OnSavedItemsChanged(
      const std::vector<mojom::PlaylistItemPtr>& items) {}
  virtual void OnFoundItemsChanged(
      const std::vector<mojom::PlaylistItemPtr>& items) {}
  virtual void OnAddedItemFromTabHelper(
      const std::vector<mojom::PlaylistItemPtr>& items) {}
};

}  // namespace playlist

#endif  // CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_PLAYLIST_TAB_HELPER_OBSERVER_H_
