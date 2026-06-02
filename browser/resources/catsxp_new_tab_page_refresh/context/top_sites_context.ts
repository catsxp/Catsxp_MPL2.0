/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { defaultTopSitesStore } from '../state/top_sites_store'
import { createUseStateHook } from '$web-common/state_store_hooks'

export const TopSitesContext = React.createContext(defaultTopSitesStore())

export const useTopSitesState = createUseStateHook(TopSitesContext)

export function useTopSitesActions() {
  return useTopSitesState((s) => s.actions)
}
