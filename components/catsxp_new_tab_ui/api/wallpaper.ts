/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { sendWithPromise } from 'chrome://resources/js/cr.js'

export function getWallpaper (): Promise<undefined | NewTab.Wallpaper> {
  return sendWithPromise('getWallpaperData')
}

export function registerViewCount (): Promise<void> {
  return sendWithPromise('registerNewTabPageView')
}

export function recordClickedAdEvent(data: NewTab.BrandedWallpaper | undefined) {
  chrome.send('recordClickedAdEvent', [data])
}
