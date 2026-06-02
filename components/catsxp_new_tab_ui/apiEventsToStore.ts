/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import getActions from './api/getActions'
import * as preferencesAPI from './api/preferences'
import * as statsAPI from './api/stats'
import * as topSitesAPI from './api/topSites'
import * as newTabAdsDataAPI from './api/newTabAdsData'
import getNTPBrowserAPI, { Background, CustomBackground } from './api/background'
import { getInitialData } from './api/initialData'
import * as backgroundData from './data/backgrounds'
import { loadTimeData } from '$web-common/loadTimeData'

async function updatePreferences (prefData: NewTab.Preferences) {
  getActions().preferencesUpdated(prefData)
}

async function updateStats (statsData: statsAPI.Stats) {
  getActions().statsUpdated(statsData)
}

async function updateNewTabAdsData (data: newTabAdsDataAPI.NewTabAdsData) {
  getActions().newTabAdsDataUpdated(data)
}

async function onMostVisitedInfoChanged (topSites: topSitesAPI.MostVisitedInfoChanged) {
  getActions().tilesUpdated(topSites.tiles)
  getActions().topSitesStateUpdated(topSites.visible, topSites.custom_links_enabled, topSites.custom_links_num)
}

async function onBackgroundUpdated (background: Background) {
  getActions().customBackgroundUpdated(background)
}

async function onCustomImageBackgroundsUpdated (backgrounds: CustomBackground[]) {
  getActions().customImageBackgroundsUpdated(backgrounds)
}

// Not marked as async so we don't return a promise
// and confuse callers
export function wireApiEventsToStore () {
  // Get initial data and dispatch to store
  getInitialData()
  .then((initialData) => {
    getActions().setInitialData(initialData)
    // Listen for API changes and dispatch to store
    topSitesAPI.addMostVistedInfoChangedListener(onMostVisitedInfoChanged)
    topSitesAPI.updateMostVisitedInfo()
    statsAPI.addChangeListener(updateStats)
    preferencesAPI.addChangeListener(updatePreferences)
    newTabAdsDataAPI.addChangeListener(updateNewTabAdsData)
    backgroundData.updateImages(initialData.catsxpBackgrounds)

    getNTPBrowserAPI().addBackgroundUpdatedListener(onBackgroundUpdated)
    getNTPBrowserAPI().addCustomImageBackgroundsUpdatedListener(onCustomImageBackgroundsUpdated)
    getNTPBrowserAPI().addSearchPromotionDisabledListener(() => getActions().searchPromotionDisabled())
    if (loadTimeData.getBoolean('vpnWidgetSupported')) {
      getActions().catsxpVPN.initialize(initialData.purchasedState)
    }
  })
  .catch(e => {
    console.error('New Tab Page fatal error:', e)
  })
}
