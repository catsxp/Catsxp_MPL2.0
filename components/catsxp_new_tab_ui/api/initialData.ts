/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as preferencesAPI from './preferences'
import * as statsAPI from './stats'
import * as wallpaper from './wallpaper'
import getNTPBrowserAPI from './background'
import getVPNServiceHandler, * as CatsxpVPN from '../api/catsxpVpn'
import { loadTimeData } from '$web-common/loadTimeData'

export type InitialData = {
  preferences: NewTab.Preferences
  stats: statsAPI.Stats
  wallpaperData?: NewTab.Wallpaper
  catsxpBackgrounds: NewTab.CatsxpBackground[]
  customImageBackgrounds: NewTab.ImageBackground[]
  catsxpRewardsSupported: boolean
  catsxpTalkSupported: boolean
  searchPromotionEnabled: boolean
  purchasedState: CatsxpVPN.PurchasedState
}

const isIncognito: boolean = chrome.extension.inIncognitoContext

// Gets all data required for the first render of the page
export async function getInitialData (): Promise<InitialData> {
  try {
    console.timeStamp('Getting initial data...')
    const [
      preferences,
      stats,
      wallpaperData,
      catsxpRewardsSupported,
      catsxpTalkSupported,
      searchPromotionEnabled,
      catsxpBackgrounds,
      customImageBackgrounds,
      purchasedState
    ] = await Promise.all([
      preferencesAPI.getPreferences(),
      statsAPI.getStats(),
      !isIncognito ? wallpaper.getWallpaper() : Promise.resolve(undefined),
      false,
      new Promise((resolve) => {
        if (!('catsxpTalk' in chrome)) {
          resolve(false)
          return
        }

        chrome.catsxpTalk.isSupported((supported: boolean) => {
          resolve(supported)
        })
      }),
      getNTPBrowserAPI().pageHandler.isSearchPromotionEnabled().then(({ enabled }) => enabled),
      getNTPBrowserAPI().pageHandler.getCatsxpBackgrounds().then(({ backgrounds }) => {
        return backgrounds.map(background => ({ type: 'catsxp', wallpaperImageUrl: background.imageUrl.url, author: background.author, link: background.link.url }))
      }),
      getNTPBrowserAPI().pageHandler.getCustomImageBackgrounds().then(({ backgrounds }) => {
        return backgrounds.map(background => ({ type: 'image', wallpaperImageUrl: background.url.url }))
      }),
      new Promise((resolve) => {
        if (loadTimeData.getBoolean('vpnWidgetSupported')) {
          getVPNServiceHandler().getPurchasedState().then(({state}) => {
            resolve(state.state)
          })
        } else {
          resolve(CatsxpVPN.PurchasedState.NOT_PURCHASED)
        }
      })
    ])
    console.timeStamp('Got all initial data.')
    return {
      preferences,
      stats,
      wallpaperData,
      catsxpBackgrounds,
      customImageBackgrounds,
      catsxpRewardsSupported,
      catsxpTalkSupported,
      searchPromotionEnabled,
      purchasedState
    } as InitialData
  } catch (e) {
    console.error(e)
    throw Error('Error getting initial data')
  }
}
