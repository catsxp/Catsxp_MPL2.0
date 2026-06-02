/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { getPlaylistActions } from './api/getPlaylistActions'
import { getPlaylistAPI } from './api/api'

async function getInitialData () {
  return getPlaylistAPI().getAllPlaylists()
}

export default function wireApiEventsToStore () {
  // Get initial data and dispatch to store
  getInitialData()
    .then(initialData => {
      getPlaylistActions().playlistLoaded(initialData.playlists)

      // TODO(sko): Add proper event listeners for changes to playlist.
      const api = getPlaylistAPI()
      api.addEventListener(e => {
        getInitialData().then(data => {
          getPlaylistActions().playlistLoaded(data.playlists)
        })
      })

      api.addMediaCachingProgressListener(
        (id, totalBytes, receivedBytes, percentComplete, timeRemaining) => {
          getPlaylistActions().cachingProgressChanged({
            id,
            totalBytes,
            receivedBytes,
            percentComplete,
            timeRemaining
          })
        }
      )

      api.addPlaylistUpdatedListener(playlist =>
        getPlaylistActions().playlistUpdated(playlist)
      )


      api.shouldShowAddMediaFromPageUI().then(({result}) => {
        getPlaylistActions().shouldShowAddMediaFromPageChanged(result)

        api.addOnActiveTabChangedListener((shouldShowAddMediaFromPageUI) => {
          getPlaylistActions().shouldShowAddMediaFromPageChanged(shouldShowAddMediaFromPageUI)
        })
      })
    })
    .catch(e => {
      console.error('Playlist page fatal error:', e)
    })
}
