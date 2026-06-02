/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { createRoot } from 'react-dom/client'
import { Provider } from 'react-redux'
import { setIconBasePath } from '@catsxp/leo/react/icon'
import Theme from 'catsxp-ui/theme/catsxp-default'
import DarkTheme from 'catsxp-ui/theme/catsxp-dark'
import '../common/defaultTrustedTypesPolicy'
import CatsxpCoreThemeProvider from '../common/CatsxpCoreThemeProvider'
import * as topSitesAPI from './api/topSites'
import { init } from './actions/new_tab_actions'
import App from './containers/app'
import { wireApiEventsToStore } from './apiEventsToStore'
import store from './store'

setIconBasePath('chrome://resources/catsxp-icons')

// Let things handle 'init'
store.dispatch(init())

function initialize () {
  console.timeStamp('loaded')
  // Get rendering going
  createRoot(document.getElementById('root')!).render(
    <Provider store={store}>
      <CatsxpCoreThemeProvider
        dark={DarkTheme}
        light={Theme}
      >
        <App />
      </CatsxpCoreThemeProvider>
    </Provider>)
}

console.timeStamp('JS start')

// Get store data going
wireApiEventsToStore()

// Perform DOM-dependent initialization when ready
document.addEventListener('DOMContentLoaded', initialize)

// Update topsite tiles when NTP gets visible.
document.addEventListener('visibilitychange', () => {
  if (document.visibilityState === 'visible') {
    topSitesAPI.updateMostVisitedInfo()
  }
})
