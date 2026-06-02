/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import store from '../store'
import { bindActionCreators, Dispatch } from 'redux'

import * as PlayerActions from '../actions/player_action_creators'

let actions: typeof PlayerActions

function getPlayerActionsForDispatch (dispatch: Dispatch) {
  return bindActionCreators(PlayerActions, dispatch)
}

// returns actions bound to dispatch.
export function getPlayerActions () {
  actions = actions || getPlayerActionsForDispatch(store.dispatch.bind(store))
  return actions
}
