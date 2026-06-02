/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { render } from 'react-dom'
import { Provider } from 'react-redux'
import { BrowserRouter } from 'react-router-dom'

import { setIconBasePath } from '@catsxp/leo/react/icon'

// Components
import App from './components/app.v1'

// Theme

import wireApiEventsToStore from './apiEventsToStore'
import startReceivingPlayerEvents from './playerEventSink'

// Utils
import store from './store'

function initialize () {
  render(
    <BrowserRouter>
      <Provider store={store}>
        <App />
      </Provider>
    </BrowserRouter>,
    document.getElementById('root')
  )
}

wireApiEventsToStore()
startReceivingPlayerEvents()
setIconBasePath('chrome-untrusted://resources/catsxp-icons')

document.addEventListener('DOMContentLoaded', initialize)
