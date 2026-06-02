/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { useShieldsApi } from '../api/shields_api_context'

export function useInitializedStatus() {
  const api = useShieldsApi()
  const { data: siteBlockInfo } = api.useGetSiteBlockInfo()
  const { data: siteSettings } = api.useGetSiteSettings()
  const getBrowserWindowHeight = api.useGetBrowserWindowHeight()
  const getAdvancedViewEnabled = api.useGetAdvancedViewEnabled()

  const initialized = Boolean(
    siteBlockInfo
      && siteSettings
      && !getBrowserWindowHeight.isPlaceholderData
      && !getAdvancedViewEnabled.isPlaceholderData,
  )

  React.useEffect(() => {
    if (initialized) {
      api.showUI()
    }
  }, [api, initialized])

  return initialized
}
