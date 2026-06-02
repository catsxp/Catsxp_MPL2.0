/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

// Import CatsxpNewsControllerMock first.
import './default/data/mockCatsxpNewsController'

import * as React from 'react'
import { Dispatch } from 'redux'
import { Provider as ReduxProvider } from 'react-redux'
// Components
import NewTabPage from '../containers/newTab'
import { getActionsForDispatch } from '../api/getActions'
import store from '../store'
import { useNewTabData, getGridSitesData } from './default/data/storybookState'
import { onChangeColoredBackground, onUseCatsxpBackground, onShowBrandedImageChanged } from './default/data/backgroundWallpaper'
import getTodayState from './default/data/todayStorybookState'
import getCatsxpVPNState from './default/data/catsxpVPNStorybookState'
import { getDataUrl, getUnpaddedAsDataUrl } from '../../common/privateCDN'
import { images, updateImages } from '../data/backgrounds'

const doNothingDispatch: Dispatch = (action: any) => action

function getActions () {
  return getActionsForDispatch(doNothingDispatch)
}

// @ts-expect-error
window.catsxpStorybookUnpadUrl = async function UnpadUrl (paddedUrl: string, mimeType = 'image/jpg'): Promise<string> {
  const response = await fetch(paddedUrl)
  const blob = await response.blob()
  const buffer = await blob.arrayBuffer()
  if (paddedUrl.endsWith('.pad')) {
    return await getUnpaddedAsDataUrl(buffer, mimeType)
  }
  // Image is already unpadded
  return await getDataUrl(buffer)
}

const StoreProvider: React.FC<React.PropsWithChildren> = ({ children }) => {
  return (
    <ReduxProvider store={store}>
     {children}
    </ReduxProvider>
  )
}

export default {
  title: 'New Tab',
  decorators: [
    (Story: any) => <StoreProvider><Story /></StoreProvider>
  ]
}

updateImages(images.map((image): NewTab.CatsxpBackground => {
  return {
    ...image,
    // eslint-disable-next-line @typescript-eslint/no-require-imports
    wallpaperImageUrl: require('../../img/newtab/backgrounds/' + image.wallpaperImageUrl)
  }
}))

export const Regular = () => {
  const doNothing = (value?: any) => value
  const state = store.getState()
  const newTabData = useNewTabData(state.newTabData)
  const gridSitesData = getGridSitesData(state.gridSitesData)
  const todayState = getTodayState()
  const catsxpVPNState = getCatsxpVPNState()

  return (
    <NewTabPage
      newTabData={newTabData}
      todayData={todayState}
      catsxpVPNData={catsxpVPNState}
      gridSitesData={gridSitesData}
      actions={getActions()}
      saveShowBackgroundImage={doNothing}
      saveShowRewards={doNothing}
      saveShowCatsxpTalk={doNothing}
      saveBrandedWallpaperOptIn={onShowBrandedImageChanged}
      saveSetAllStackWidgets={doNothing}
      setCatsxpBackground={onUseCatsxpBackground}
      chooseNewCustomBackgroundImage={doNothing}
      setCustomImageBackground={doNothing}
      removeCustomImageBackground={doNothing}
      setColorBackground={onChangeColoredBackground}
    />
  )
}
