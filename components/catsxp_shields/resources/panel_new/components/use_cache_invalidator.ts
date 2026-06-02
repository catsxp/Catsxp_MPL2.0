/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { useShieldsApi } from '../api/shields_api_context'
import { debounce } from '$web-common/debounce'

export function useCacheInvalidator() {
  const api = useShieldsApi()

  // Invalidate caches when panel is (re)displayed from the WebUI cache.
  React.useEffect(() => {
    const listener = debounce(() => {
      if (document.visibilityState === 'visible') {
        api.getAdvancedViewEnabled.reset()
        api.getBrowserWindowHeight.reset()
        api.getSiteBlockInfo.reset()
        api.getSiteSettings.reset()
        api.repeatedReloadsDetected.reset()
        api.areAnyBlockedElementsPresent.reset()
        api.updateFavicon()
      }
    }, 30)
    document.addEventListener('visibilitychange', listener)
    return () => document.removeEventListener('visibilitychange', listener)
  }, [api])
}
