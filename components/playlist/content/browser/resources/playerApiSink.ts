/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { getPlayerActions } from './api/getPlayerActions'
import { PlayerMessagePayload } from './api/playerApi'
import { types } from './constants/player_types'

export function handlePlayerMessage (payload: PlayerMessagePayload) {
  switch (payload.actionType) {
    case types.PLAYLIST_ITEM_SELECTED: {
      getPlayerActions().selectPlaylistItem(payload)
      break
    }
    case types.SELECTED_PLAYLIST_UPDATED: {
      getPlayerActions().selectedPlaylistUpdated(payload)
      break
    }
  }
}

export default function startReceivingAPIRequest () {
  window.onmessage = e => {
    if (e.origin !== 'chrome-untrusted://playlist') {
      console.error(`Invalid origin: ${e.origin}`)
      return
    }

    handlePlayerMessage(e.data)
  }
}
