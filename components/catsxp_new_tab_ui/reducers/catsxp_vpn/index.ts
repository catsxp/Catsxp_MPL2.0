/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { createReducer } from 'redux-act'
import * as Actions from '../../actions/catsxp_vpn_actions'
import * as CatsxpVPN from '../../api/catsxpVpn'

// Set true to initialzied when final purchased state is received once.
// Before that, vpn card is not rendered.
export type CatsxpVPNState = {
  purchasedState: CatsxpVPN.PurchasedState
  connectionState: CatsxpVPN.ConnectionState
  selectedRegion: CatsxpVPN.Region
}

const defaultState: CatsxpVPNState = {
  purchasedState: CatsxpVPN.PurchasedState.NOT_PURCHASED,
  connectionState: CatsxpVPN.ConnectionState.DISCONNECTED,
  selectedRegion: new CatsxpVPN.Region()
}

const reducer = createReducer<CatsxpVPNState>({}, defaultState)

reducer.on(Actions.connectionStateChanged, (state, payload): CatsxpVPNState => {
  return {
    ...state,
    connectionState: payload
  }
})

reducer.on(Actions.purchasedStateChanged, (state, payload): CatsxpVPNState => {
  // Don't update if it's in-progress to prevent unnecessary vpn card page chanage.
  const isLoading = payload === CatsxpVPN.PurchasedState.LOADING

  return {
    ...state,
    purchasedState:
      isLoading
        ? state.purchasedState
        : payload
  }
})

reducer.on(Actions.selectedRegionChanged, (state, payload): CatsxpVPNState => {
  return {
    ...state,
    selectedRegion: payload
  }
})

export default reducer
