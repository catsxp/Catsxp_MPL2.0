/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { combineReducers } from 'redux'
import * as storage from '../storage/new_tab_storage'

// Reducers
import newTabStateReducer from './new_tab_reducer'
import gridSitesReducer from './grid_sites_reducer'
import rewardsReducer from './rewards_reducer'
import { stackWidgetReducer } from './stack_widget_reducer'
import todayReducer, { CatsxpNewsState } from './today'
import catsxpVPNReducer, { CatsxpVPNState } from './catsxp_vpn'

export type ApplicationState = NewTab.ApplicationState & {
  today: CatsxpNewsState
  catsxpVPN: CatsxpVPNState
}

export const newTabReducers = (state: NewTab.State | undefined, action: any) => {
  if (state === undefined) {
    state = storage.load()
  }

  const startingState = state
  state = newTabStateReducer(state, action)
  state = rewardsReducer(state, action)
  state = stackWidgetReducer(state, action)

  if (state && state !== startingState) {
    storage.debouncedSave(state)
  }

  return state
}

export const mainNewTabReducer = combineReducers<ApplicationState>({
  newTabData: newTabReducers,
  gridSitesData: gridSitesReducer,
  today: todayReducer,
  catsxpVPN: catsxpVPNReducer
})

export const newTabReducer = newTabStateReducer
