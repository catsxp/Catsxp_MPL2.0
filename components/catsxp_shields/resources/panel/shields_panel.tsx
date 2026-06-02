/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { render } from 'react-dom'
import { initLocale } from 'catsxp-ui'

import { setIconBasePath } from '@catsxp/leo/react/icon'

import { loadTimeData } from '$web-common/loadTimeData'
import CatsxpCoreThemeProvider from '$web-common/CatsxpCoreThemeProvider'
import { PanelWrapper } from './style'
import getPanelBrowserAPI from './api/panel_browser_api'
import Container from './container'
import { useSiteBlockInfoData, useSiteSettingsData } from './state/hooks'
import DataContext from './state/context'
import { ViewType } from './state/component_types'

setIconBasePath('//resources/catsxp-icons')

function App () {
  const { siteBlockInfo } = useSiteBlockInfoData()
  const { siteSettings, getSiteSettings } = useSiteSettingsData()
  const [viewType, setViewType] = React.useState<ViewType>(ViewType.Main)

  const store = {
    siteBlockInfo,
    siteSettings,
    getSiteSettings,
    viewType,
    setViewType
  }

  React.useEffect(() => {
    const onVisibilityChange = () => {
      if (document.visibilityState === 'visible') {
        getPanelBrowserAPI().panelHandler.showUI()
        getPanelBrowserAPI().dataHandler.updateFavicon()
        setViewType(ViewType.Main) /* Reset the view back to main panel */
      }
    }

    document.addEventListener('visibilitychange', onVisibilityChange)

    return () => {
      document.removeEventListener('visibilitychange', onVisibilityChange)
    }
  }, [])

  return (<DataContext.Provider
    value={store}
  >
    <CatsxpCoreThemeProvider>
      <PanelWrapper>
        <Container />
      </PanelWrapper>
    </CatsxpCoreThemeProvider>
  </DataContext.Provider>)
}

function initialize () {
  initLocale(loadTimeData.data_)
  render(<App />, document.getElementById('mountPoint'),
  () => {
    getPanelBrowserAPI().panelHandler.showUI()
  })
}

document.addEventListener('DOMContentLoaded', initialize)
