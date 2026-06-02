/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import {
  Playlist,
  PlaylistItem
} from 'gen/catsxp/components/playlist/core/common/mojom/playlist.mojom.m'

import { types } from '../constants/player_types'

function getPlayerWindow () {
  return (document.getElementById('player') as HTMLIFrameElement)?.contentWindow
}

export type ItemSelectedPayload = {
  currentList: Playlist
  currentItem: PlaylistItem
}

export type SelectedPlaylistUpdatedPayload = {
  currentList: Playlist
}

export type PlayerMessagePayload =
  | ({
      actionType: types.PLAYLIST_ITEM_SELECTED
    } & ItemSelectedPayload)
  | ({
      actionType: types.SELECTED_PLAYLIST_UPDATED
    } & SelectedPlaylistUpdatedPayload)

export default function postMessageToPlayer (payload: PlayerMessagePayload) {
  const playerWindow = getPlayerWindow()
  if (!playerWindow) {
    console.error("Couldn't find player window")
    return
  }

  playerWindow.postMessage(payload, 'chrome-untrusted://playlist-player')
}
