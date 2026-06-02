/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import {
  PageHandlerFactory,
  Playlist,
  PlaylistEvent,
  PlaylistPageCallbackRouter,
  PlaylistPageHandlerRemote,
  PlaylistServiceObserverCallbackRouter,
  PlaylistServiceRemote,
} from 'gen/catsxp/components/playlist/core/common/mojom/playlist.mojom.m.js'

import { getPlaylistActions } from './getPlaylistActions'

type PlaylistEventListener = (event: PlaylistEvent) => void

let apiInstance: API

class API {
  #pageCallbackRouter = new PlaylistPageCallbackRouter()
  #playlistServiceObserverCallbackRouter = new PlaylistServiceObserverCallbackRouter()
  #playlistService = new PlaylistServiceRemote()
  #pageHandler = new PlaylistPageHandlerRemote()

  constructor() {
    const factory = PageHandlerFactory.getRemote()
    factory.createPageHandler(
      this.#pageCallbackRouter.$.bindNewPipeAndPassRemote(),
      this.#playlistServiceObserverCallbackRouter.$.bindNewPipeAndPassRemote(),
      this.#playlistService.$.bindNewPipeAndPassReceiver(),
      this.#pageHandler.$.bindNewPipeAndPassReceiver()
    )
  }

  async getAllPlaylists() {
    return this.#playlistService.getAllPlaylists()
  }

  async getPlaylist(id: string) {
    return this.#playlistService.getPlaylist(id)
  }

  createPlaylist(playlist: Playlist) {
    this.#playlistService.createPlaylist(playlist)
  }

  renamePlaylist(playlistId: string, newName: string) {
    this.#playlistService
      .renamePlaylist(playlistId, newName)
      .then(({ updatedPlaylist }) => {
        getPlaylistActions().playlistUpdated(updatedPlaylist)
      })
  }

  removePlaylist(playlistId: string) {
    this.#playlistService.removePlaylist(playlistId)
  }

  addMediaFilesFromActiveTabToPlaylist(playlistId: string) {
    this.#playlistService.addMediaFilesFromActiveTabToPlaylist(
      playlistId,
      /* canCache */ true
    )
  }

  moveItemFromPlaylist(playlistId: string, itemId: string[]) {
    this.#pageHandler.showMoveItemsUI(playlistId, itemId)
  }

  removeItemFromPlaylist(playlistId: string, itemId: string) {
    this.#playlistService.removeItemFromPlaylist(playlistId, itemId)
  }

  copyDownloadLink(itemId: string) {
    this.#playlistService.copyDownloadLink(itemId)
  }

  openItemDirPath(itemId: string) {
    this.#playlistService.openItemDirPath(itemId)
  }

  recoverLocalData(
    playlistItemId: string,
    updateMediaSrcBeforeRecovery = false
  ) {
    this.#playlistService.recoverLocalDataForItem(
      playlistItemId,
      updateMediaSrcBeforeRecovery
    )
  }

  updateItemLastPlayedPosition(
    playlistItemId: string,
    lastPlayedPosition: number
  ) {
    this.#playlistService.updateItemLastPlayedPosition(
      playlistItemId,
      lastPlayedPosition
    )
  }

  removeLocalData(playlistItemId: string) {
    this.#playlistService.removeLocalDataForItem(playlistItemId)
  }

  showCreatePlaylistUI() {
    this.#pageHandler.showCreatePlaylistUI()
  }

  showRemovePlaylistUI(playlistId: string) {
    this.#pageHandler.showRemovePlaylistUI(playlistId)
  }

  openSettingsPage() {
    this.#pageHandler.openSettingsPage()
  }

  closePanel() {
    this.#pageHandler.closePanel()
  }

  showAddMediaToPlaylistUI() {
    this.#pageHandler.showAddMediaToPlaylistUI()
  }

  reorderItemFromPlaylist(
    playlistId: string,
    itemId: string,
    position: number,
    callback: (result: boolean) => void
  ) {
    this.#playlistService
      .reorderItemFromPlaylist(playlistId, itemId, position)
      .then(({ result }) => callback(result))
  }

  reorderPlaylist(
    playlistId: string,
    position: number,
    callback: (result: boolean) => void
  ) {
    this.#playlistService
      .reorderPlaylist(playlistId, position)
      .then(({ result }) => callback(result))
  }

  async shouldShowAddMediaFromPageUI() {
    return this.#pageHandler.shouldShowAddMediaFromPageUI()
  }

  // Events --------------------------------------------------------------------
  addEventListener(listener: PlaylistEventListener) {
    this.#playlistServiceObserverCallbackRouter.onEvent.addListener(listener)
  }

  addMediaCachingProgressListener(
    listener: (
      id: string,
      totalBytes: bigint,
      receivedBytes: bigint,
      percentComplete: number,
      timeRemaining: string
    ) => void
  ) {
    this.#playlistServiceObserverCallbackRouter.onMediaFileDownloadProgressed.addListener(listener)
    this.#playlistServiceObserverCallbackRouter.onMediaFileDownloadScheduled.addListener(
      (id:string)=>listener(id, BigInt(0), BigInt(0), 0, ''))
  }

  addPlaylistUpdatedListener(listener: (playlist: Playlist) => void) {
    this.#playlistServiceObserverCallbackRouter.onPlaylistUpdated.addListener(listener)
  }

  addOnActiveTabChangedListener(listener: (shouldShowAddMediaFromPageUI: boolean) => void) {
    this.#pageCallbackRouter.onActiveTabChanged.addListener(listener)
  }
}

export function getPlaylistAPI(): API {
  if (!apiInstance) {
    apiInstance = new API()
  }
  return apiInstance
}
