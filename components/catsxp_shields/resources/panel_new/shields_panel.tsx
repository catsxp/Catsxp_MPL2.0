/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { createRoot } from 'react-dom/client'
import { setIconBasePath } from '@catsxp/leo/react/icon'

import { loadTimeData } from '$web-common/loadTimeData'
import { ShieldsPanelProxy } from './api/shields_panel_proxy'
import { createShieldsApi } from './api/shields_api'
import { ShieldsApiProvider } from './api/shields_api_context'
import { App } from './components/app'

setIconBasePath('//resources/catsxp-icons')

function hasReloadsDetectedFlag() {
  const urlParams = new URLSearchParams(window.location.search)
  return urlParams.get('mode') === 'afterRepeatedReloads'
}

function createBrowserShieldsApi() {
  const proxy = ShieldsPanelProxy.getInstance()
  return createShieldsApi({
    dataHandler: proxy.dataHandler,
    panelHandler: proxy.panelHandler,
    createUIHandlerRemote: (impl) => proxy.createUIHandlerRemote(impl),
    openTab: (url) => chrome.tabs.create({ url, active: true }),
    loadTimeState: {
      isHttpsByDefaultEnabled: loadTimeData.getBoolean(
        'isHttpsByDefaultEnabled',
      ),
      isTorProfile: loadTimeData.getBoolean('isTorProfile'),
      showStrictFingerprintingMode: loadTimeData.getBoolean(
        'showStrictFingerprintingMode',
      ),
      isWebcompatExceptionsServiceEnabled: loadTimeData.getBoolean(
        'isWebcompatExceptionsServiceEnabled',
      ),
      isCatsxpForgetFirstPartyStorageFeatureEnabled: loadTimeData.getBoolean(
        'isCatsxpForgetFirstPartyStorageFeatureEnabled',
      ),
      repeatedReloadsDetected: hasReloadsDetectedFlag(),
    },
  })
}

createRoot(document.getElementById('root')!).render(
  <ShieldsApiProvider api={createBrowserShieldsApi()}>
    <App />
  </ShieldsApiProvider>,
)
