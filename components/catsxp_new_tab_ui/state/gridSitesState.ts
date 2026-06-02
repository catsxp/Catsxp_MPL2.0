/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

export function tilesUpdated (
  state: NewTab.GridSitesState,
  sitesData: NewTab.Site[]
): NewTab.GridSitesState {
  state = { ...state, gridSites: sitesData }
  return state
}

export function showTilesRemovedNotice (
  state: NewTab.GridSitesState,
  shouldShow: boolean
): NewTab.GridSitesState {
  state = { ...state, shouldShowSiteRemovedNotification: shouldShow }
  return state
}
