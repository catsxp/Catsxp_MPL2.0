/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { combineReducers } from 'redux'

// Utils
import adblockReducer from './adblock_reducer'

export default combineReducers<AdBlock.ApplicationState>({
  adblockData: adblockReducer,
})
