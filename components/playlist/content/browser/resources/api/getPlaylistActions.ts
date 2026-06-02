/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import store from '../store'

import * as PlaylistActions from '../actions/playlist_action_creators'
import { bindActionCreators, Dispatch } from 'redux'

let actions: typeof PlaylistActions

function getPlaylistActionsForDispatch (dispatch: Dispatch) {
  return bindActionCreators(PlaylistActions, dispatch)
}

// returns actions bound to dispatch.
export function getPlaylistActions () {
  actions = actions || getPlaylistActionsForDispatch(store.dispatch.bind(store))
  return actions
}
