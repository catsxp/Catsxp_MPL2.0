/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { BrowserProfile } from '../api/welcome_browser_proxy'

export const getUniqueBrowserTypes = (browserProfiles: BrowserProfile[]) => {
  const browsersTypes = browserProfiles.map((profile) => profile.browserType)
  // We use set here to remove dupes and maintain order
  return Array.from(new Set(browsersTypes))
}
