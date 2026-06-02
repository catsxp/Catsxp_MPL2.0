/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { createRoot } from 'react-dom/client'
import { initLocale } from 'catsxp-ui'

import { loadTimeData } from '$web-common/loadTimeData'

import CatsxpCoreThemeProvider from '$web-common/CatsxpCoreThemeProvider'

import MainContainer from './main_container'
import DataContextProvider from './state/data-context-provider'

function App () {
  return (
    <DataContextProvider>
      <CatsxpCoreThemeProvider>
        <MainContainer />
      </CatsxpCoreThemeProvider>
    </DataContextProvider>
  )
}

function initialize () {
  initLocale(loadTimeData.data_)
  const root = createRoot(document.getElementById('root')!)
  root.render(<App />)
}

document.addEventListener('DOMContentLoaded', initialize)
