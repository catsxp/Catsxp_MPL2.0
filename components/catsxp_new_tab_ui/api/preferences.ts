/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { addWebUiListener, sendWithPromise } from 'chrome://resources/js/cr.js'

//
// Manages get and set of NTP preference data
// Ensures everything to do with communication
// with the WebUI backend is all in 1 place,
// especially string keys.
//

type PreferencesUpdatedHandler = (prefData: NewTab.Preferences) => void

export function getPreferences (): Promise<NewTab.Preferences> {
  return sendWithPromise('getNewTabPagePreferences')
}

export function sendSavePref (key: string, value: any) {
  chrome.send('saveNewTabPagePref', [key, value])
}

export function saveShowBackgroundImage (value: boolean): void {
  sendSavePref('showBackgroundImage', value)
}

export function saveShowRewards (value: boolean): void {
  sendSavePref('showRewards', value)
}

export function saveShowCatsxpTalk (value: boolean): void {
  sendSavePref('showCatsxpTalk', value)
}

export function saveBrandedWallpaperOptIn (value: boolean): void {
  sendSavePref('brandedWallpaperOptIn', value)
}

export function saveIsBrandedWallpaperNotificationDismissed (value: boolean): void {
  sendSavePref('isBrandedWallpaperNotificationDismissed', value)
}

export function saveSetAllStackWidgets (visible: boolean): void {
  sendSavePref('hideAllWidgets', !visible)
}

export function addChangeListener (listener: PreferencesUpdatedHandler): void {
  addWebUiListener('preferences-changed', listener)
}
