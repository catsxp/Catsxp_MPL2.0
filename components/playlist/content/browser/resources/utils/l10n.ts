/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { getLocale } from '$web-common/locale'

export type Message =
  | 'catsxpDefaultPlaylistName'
  | 'catsxpPlaylistContextMenuEdit'
  | 'catsxpPlaylistContextMenuShare'
  | 'catsxpPlaylistContextMenuKeepForOfflinePlaying'
  | 'catsxpPlaylistContextMenuRemovePlayedContents'
  | 'catsxpPlaylistContextMenuMove'
  | 'catsxpPlaylistContextMenuRemoveOfflineData'
  | 'catsxpPlaylistContextMenuRemoveFromPlaylist'
  | 'catsxpPlaylistContextMenuRenamePlaylist'
  | 'catsxpPlaylistContextMenuDeletePlaylist'
  | 'catsxpPlaylistContextMenuViewOriginalPage'
  | 'catsxpPlaylistContextMenuViewCopyDownloadLink'
  | 'catsxpPlaylistContextMenuViewOpenItemDirPath'
  | 'catsxpPlaylistEmptyFolderMessage'
  | 'catsxpPlaylistTooltipCreatePlaylistFolder'
  | 'catsxpPlaylistTooltipOpenPlaylistSettings'
  | 'catsxpPlaylistTooltipClosePanel'
  | 'catsxpPlaylistTooltipPlay'
  | 'catsxpPlaylistTooltipPause'
  | 'catsxpPlaylistTooltipNext'
  | 'catsxpPlaylistTooltipPrevious'
  | 'catsxpPlaylistTooltipToggleMuted'
  | 'catsxpPlaylistTooltipShuffle'
  | 'catsxpPlaylistTooltipRewind'
  | 'catsxpPlaylistTooltipForward'
  | 'catsxpPlaylistTooltipClose'
  | 'catsxpPlaylistTooltipLoopOff'
  | 'catsxpPlaylistTooltipLoopOne'
  | 'catsxpPlaylistTooltipLoopAll'
  | 'catsxpPlaylistFailedToPlayTitle'
  | 'catsxpPlaylistFailedToPlayDescription'
  | 'catsxpPlaylistFailedToPlayRecover'
  | 'catsxpPlaylistAlertDismiss'
  | 'catsxpPlaylistAddMediaFromPage'

export function getLocalizedString(message: Message) {
  return getLocale(message)
}
