/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import * as PlaylistMojo from 'gen/catsxp/components/playlist/core/common/mojom/playlist.mojom.m.js'

interface Props {
  playlists: PlaylistMojo.Playlist[]
  selectedPlaylist: PlaylistMojo.Playlist | undefined

  onSelectPlaylist: (playlistId: string) => void
  onCreatePlaylist: (playlist: PlaylistMojo.Playlist) => void
  onRemovePlaylist: (playlistId: string) => void
};

export default function PlaylistSelect ({
    playlists,
    selectedPlaylist,
    onSelectPlaylist,
    onCreatePlaylist,
    onRemovePlaylist
}: Props) {
   const onClickCreateButton = React.useCallback((e) => {
      const name = window.prompt('Enter a name for the new playlist', 'New Playlist')
      if (!name) return
      onCreatePlaylist({ id: undefined, name, items: [] })
    }, [onCreatePlaylist])

  const onClickRemoveButton = React.useCallback(_ => {
    if (!selectedPlaylist?.id) return
    onRemovePlaylist(selectedPlaylist.id)
  }, [onRemovePlaylist, selectedPlaylist])

   return (
     <div>
        <select onChange={e => onSelectPlaylist(e.target.value)}>
        {
          playlists.map(playlist => (
            <option key={playlist.id} value={playlist.id}>{playlist.name ? playlist.name : 'No Name'}</option>
          ))
        }
        </select>
        <button onClick={onClickCreateButton}>Create a new playlist</button>
        <button onClick={onClickRemoveButton}>Remove this playlist</button>
     </div>
   )
 }
