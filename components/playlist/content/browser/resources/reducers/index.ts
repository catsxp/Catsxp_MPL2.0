/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { ApplicationState } from 'components/playlist/content/browser/resources/reducers/states'
import { combineReducers } from 'redux'

// Utils
import playerReducer from './player_reducer'
import playlistReducer from './playlist_reducer'

export default combineReducers<ApplicationState>({
  playlistData: playlistReducer,
  playerState: playerReducer
})
