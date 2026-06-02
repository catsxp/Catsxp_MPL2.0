/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

export function faviconURL(url: string) {
  return 'chrome://favicon2/?size=64&pageUrl=' + encodeURIComponent(url)
}
