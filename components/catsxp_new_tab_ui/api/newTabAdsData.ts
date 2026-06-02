/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as Cr from 'chrome://resources/js/cr.js'

export type NewTabAdsData = {
  needsBrowserUpgradeToServeAds: boolean
}

type NewTabAdsDataUpdatedHandler = (data: NewTabAdsData) => void

export function getNewTabAdsData (): Promise<NewTabAdsData> {
  return Cr.sendWithPromise('getNewTabAdsData')
}

export function addChangeListener (listener: NewTabAdsDataUpdatedHandler): void {
  Cr.addWebUiListener('new-tab-ads-data-updated', listener)
}
