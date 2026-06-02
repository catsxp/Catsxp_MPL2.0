/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import DataContext from './state/context'
import { shouldPlayAnimations } from './state/hooks'
import { ViewType } from './state/component_types'

import HelpImprove from './components/help-improve'
import ImportInProgress from './components/import-in-progress'
import Background from './components/background'
import Welcome from './components/welcome'
import Loader from './components/loader'
import HelpWDP from './components/help-wdp'

const SelectBrowser = React.lazy(() => import('./components/select-browser'))
const SelectProfile = React.lazy(() => import('./components/select-profile'))
const SelectTheme = React.lazy(() => import('./components/select-theme'))
const SetupComplete = React.lazy(() => import('./components/setup-complete'))

function MainContainer () {
  const { viewType, setViewType } = React.useContext(DataContext)

  let mainEl = null

  if (viewType === ViewType.ImportSelectBrowser) {
    mainEl = <SelectBrowser />
  }

  if (viewType === ViewType.ImportSelectProfile) {
    mainEl = <SelectProfile />
  }

  if (viewType === ViewType.ImportSelectTheme) {
    mainEl = <SelectTheme />
  }

  if (viewType === ViewType.ImportInProgress) {
    mainEl = <ImportInProgress />
  }

  if (viewType === ViewType.ImportSucceeded) {
    mainEl = <SetupComplete />
  }

  if (viewType === ViewType.ImportFailed) {
    mainEl = <p>Failed...</p>
  }

  if (viewType === ViewType.HelpImprove) {
    mainEl = <HelpImprove />
  }

  if (viewType === ViewType.DefaultBrowser) {
    mainEl = <Welcome />
  }

  if (viewType === ViewType.HelpWDP) {
    mainEl = <HelpWDP />
  }

  const onBackgroundImgLoad = () => {
    setViewType(ViewType.DefaultBrowser)
  }

  return (
    <Background
      static={!shouldPlayAnimations}
      onLoad={onBackgroundImgLoad}
    >
      <React.Suspense fallback={<Loader />}>
        {mainEl}
      </React.Suspense>
    </Background>
  )
}

export default MainContainer
