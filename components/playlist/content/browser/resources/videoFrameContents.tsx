/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { render } from 'react-dom'
import { Provider } from 'react-redux'

import store from './store'

import Player from './components/player'
import startReceivingAPIRequest from './playerApiSink'
import { setIconBasePath } from '@catsxp/leo/react/icon'

function initialize () {
  render(
    <Provider store={store}>
      <Player />
    </Provider>,
    document.getElementById('root')
  )
}

startReceivingAPIRequest()
setIconBasePath('chrome-untrusted://resources/catsxp-icons')

document.addEventListener('DOMContentLoaded', initialize)
