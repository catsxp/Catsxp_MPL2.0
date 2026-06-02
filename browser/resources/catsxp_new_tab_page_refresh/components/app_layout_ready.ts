/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { useCatsxpNews } from '../../../../components/catsxp_news/browser/resources/shared/Context'

import { useNewTabState } from '../context/new_tab_context'
import { useTopSitesState } from '../context/top_sites_context'

// Returns a value indicating whether the search component is ready for layout
// based on application state initialization status.
export function useSearchLayoutReady() {
  const topSitesInitialized = useTopSitesState((s) => s.initialized)
  return topSitesInitialized
}

// Returns a value indicating whether the widget component is ready for layout
// based on application initialization status.
export function useWidgetLayoutReady() {
  const newTabInitialized = useNewTabState((s) => s.initialized)
  const newsInitialized = useCatsxpNewsInitialized()

  return (
    newTabInitialized && newsInitialized
  )
}

function useCatsxpNewsInitialized() {
  const newsFeatureEnabled = useNewTabState((s) => s.newsFeatureEnabled)
  if (!newsFeatureEnabled) {
    return true
  }
  return useCatsxpNews().isShowOnNTPPrefEnabled !== undefined
}
