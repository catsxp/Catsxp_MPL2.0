/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as Cr from 'chrome://resources/js/cr.js'

export type TorTabData = {
  torCircuitEstablished: boolean
  torInitProgress: string
}

type TorTabDataUpdatedHandler = (data: TorTabData) => void

export function getTorTabData (): Promise<TorTabData> {
  return Cr.sendWithPromise('getNewTabPageTorProperties')
}

export function addChangeListener (listener: TorTabDataUpdatedHandler): void {
  Cr.addWebUiListener('tor-tab-data-updated', listener)
}
