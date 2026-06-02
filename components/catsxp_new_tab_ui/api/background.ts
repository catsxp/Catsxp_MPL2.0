/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as CatsxpNewTabPage from 'gen/catsxp/components/catsxp_new_tab_ui/catsxp_new_tab_page.mojom.m.js'
import * as NTPBackgroundMedia from 'gen/catsxp/components/ntp_background_images/browser/mojom/ntp_background_images.mojom.m.js'

import { images as backgrounds, solidColorsForBackground, gradientColorsForBackground } from '../data/backgrounds'

// Provide access to all the generated types
export * from 'gen/catsxp/components/catsxp_new_tab_ui/catsxp_new_tab_page.mojom.m.js'

/**
 * Generates a random image for new tab backgrounds
 */
export const randomBackgroundImage = (): NewTab.CatsxpBackground => {
  const randomIndex: number = Math.floor(Math.random() * backgrounds.length)
  const image: NewTab.CatsxpBackground = { ...backgrounds[randomIndex], random: true }
  return image
}

export const randomColorBackground = (color: string): NewTab.BackgroundWallpaper => {
  console.assert(color === CatsxpNewTabPage.RANDOM_SOLID_COLOR_VALUE || color === CatsxpNewTabPage.RANDOM_GRADIENT_COLOR_VALUE)

  const targetColors = color === CatsxpNewTabPage.RANDOM_SOLID_COLOR_VALUE ? solidColorsForBackground : gradientColorsForBackground
  const randomIndex: number = Math.floor(Math.random() * targetColors.length)
  const randomColor: NewTab.ColorBackground = {
    ...targetColors[randomIndex],
    random: true
  }
  return randomColor
}

interface API {
  pageCallbackRouter: CatsxpNewTabPage.PageCallbackRouter
  pageHandler: CatsxpNewTabPage.PageHandlerRemote
  newTabMetrics: CatsxpNewTabPage.NewTabMetricsRemote
  sponsoredRichMediaAdEventHandler: NTPBackgroundMedia.SponsoredRichMediaAdEventHandlerRemote
  addBackgroundUpdatedListener: (listener: BackgroundUpdated) => void
  addCustomImageBackgroundsUpdatedListener: (listener: CustomImageBackgroundsUpdated) => void
  addSearchPromotionDisabledListener: (listener: () => void) => void
}

type BackgroundUpdated = (background: CatsxpNewTabPage.Background) => void
type CustomImageBackgroundsUpdated = (backgrounds: CatsxpNewTabPage.CustomBackground[]) => void

let ntpBrowserAPIInstance: API

class NTPBrowserAPI implements API {
  pageCallbackRouter = new CatsxpNewTabPage.PageCallbackRouter()
  pageHandler = new CatsxpNewTabPage.PageHandlerRemote()
  newTabMetrics = new CatsxpNewTabPage.NewTabMetricsRemote()
  sponsoredRichMediaAdEventHandler = new NTPBackgroundMedia.SponsoredRichMediaAdEventHandlerRemote()

  constructor () {
    const factory = CatsxpNewTabPage.PageHandlerFactory.getRemote()
    factory.createPageHandler(
      this.pageCallbackRouter.$.bindNewPipeAndPassRemote(),
      this.pageHandler.$.bindNewPipeAndPassReceiver(),
      this.newTabMetrics.$.bindNewPipeAndPassReceiver(),
      this.sponsoredRichMediaAdEventHandler.$.bindNewPipeAndPassReceiver()
    )
  }

  addBackgroundUpdatedListener (listener: BackgroundUpdated) {
    this.pageCallbackRouter.onBackgroundUpdated.addListener(listener)
  }

  addCustomImageBackgroundsUpdatedListener (listener: CustomImageBackgroundsUpdated) {
    this.pageCallbackRouter.onCustomImageBackgroundsUpdated.addListener(listener)
  }

  addSearchPromotionDisabledListener (listener: () => void) {
    this.pageCallbackRouter.onSearchPromotionDisabled.addListener(listener)
  }
}

export default function getNTPBrowserAPI () {
  if (!ntpBrowserAPIInstance) {
    ntpBrowserAPIInstance = new NTPBrowserAPI()
  }
  return ntpBrowserAPIInstance
}
