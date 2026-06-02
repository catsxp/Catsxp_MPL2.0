/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

// Redux API
import { createStore, applyMiddleware } from 'redux'

// Feature core reducer
import { mainNewTabReducer } from './reducers'
import catsxpVPNAsyncHandler from './async/catsxp_vpn'
import todayAsyncHandler from './async/today'

export default createStore(
  mainNewTabReducer,
  applyMiddleware(todayAsyncHandler, catsxpVPNAsyncHandler)
)
