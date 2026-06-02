/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { Dispatch } from 'redux'
import { connect } from 'react-redux'

// Components
import NewTabPage from './newTab'

// Utils
import * as PreferencesAPI from '../api/preferences'
import getNTPBrowserAPI from '../api/background'
import { getActionsForDispatch } from '../api/getActions'

// Types
import { NewTabActions } from '../constants/new_tab_types'
import { ApplicationState } from '../reducers'
import { CatsxpNewsState } from '../reducers/today'
import { CatsxpVPNState } from '../reducers/catsxp_vpn'

interface Props {
  actions: NewTabActions
  newTabData: NewTab.State
  gridSitesData: NewTab.GridSitesState
  catsxpNewsData: CatsxpNewsState,
  catsxpVPNData: CatsxpVPNState
}

function DefaultPage (props: Props) {
  const { newTabData, catsxpNewsData, catsxpVPNData, gridSitesData, actions } = props

  // don't render if user prefers an empty page
  if (props.newTabData.showEmptyPage && !props.newTabData.isIncognito) {
    return <div />
  }

  return (
    <NewTabPage
      newTabData={newTabData}
      todayData={catsxpNewsData}
      catsxpVPNData={catsxpVPNData}
      gridSitesData={gridSitesData}
      actions={actions}
      saveShowBackgroundImage={PreferencesAPI.saveShowBackgroundImage}
      saveShowRewards={PreferencesAPI.saveShowRewards}
      saveShowCatsxpTalk={PreferencesAPI.saveShowCatsxpTalk}
      saveBrandedWallpaperOptIn={PreferencesAPI.saveBrandedWallpaperOptIn}
      saveSetAllStackWidgets={PreferencesAPI.saveSetAllStackWidgets}
      chooseNewCustomBackgroundImage={() => getNTPBrowserAPI().pageHandler.chooseLocalCustomBackground() }
      setCustomImageBackground={background => getNTPBrowserAPI().pageHandler.useCustomImageBackground(background) }
      removeCustomImageBackground={background => getNTPBrowserAPI().pageHandler.removeCustomImageBackground(background) }
      setCatsxpBackground={selectedBackground => getNTPBrowserAPI().pageHandler.useCatsxpBackground(selectedBackground)}
      setColorBackground={(color, useRandomColor) => getNTPBrowserAPI().pageHandler.useColorBackground(color, useRandomColor) }
    />
  )
}

const mapStateToProps = (state: ApplicationState): Partial<Props> => ({
  newTabData: state.newTabData,
  gridSitesData: state.gridSitesData,
  catsxpNewsData: state.today,
  catsxpVPNData: state.catsxpVPN,
})

const mapDispatchToProps = (dispatch: Dispatch): Partial<Props> => {
  return {
    actions: getActionsForDispatch(dispatch)
  }
}

export default connect(
  mapStateToProps,
  mapDispatchToProps
)(DefaultPage)
