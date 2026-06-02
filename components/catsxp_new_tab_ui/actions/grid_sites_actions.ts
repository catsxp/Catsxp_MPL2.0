/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

// Types
import { types } from '../constants/grid_sites_types'
import { action } from 'typesafe-actions'

export const tilesUpdated = (gridSites: NewTab.Site[]) => {
  return action(types.TILES_UPDATED, { gridSites })
}

export const tileRemoved = (url: string) => {
  return action(types.TILE_REMOVED, { url })
}

export const tilesReordered = (gridSites: NewTab.Site[],
    oldPos: number, newPos: number) => {
  return action(types.TILES_REORDERED, { gridSites, oldPos, newPos })
}

export const restoreDefaultTiles = () => {
  return action(types.RESTORE_DEFAULT_TILES, {})
}

export const showTilesRemovedNotice = (shouldShow: boolean) => {
  return action(types.SHOW_TILES_REMOVED_NOTICE, { shouldShow })
}

export const undoRemoveTile = () => {
  return action(types.UNDO_REMOVE_TILE, {})
}
