/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { StateStore, createStateStore } from '$web-common/state_store'

import {
  ShieldsStats,
  ClockFormat,
} from 'gen/catsxp/browser/ui/webui/catsxp_new_tab_page_refresh/catsxp_new_tab_page.mojom.m.js'

export { ShieldsStats, ClockFormat }

export interface NewTabState {
  initialized: boolean
  showClock: boolean
  clockFormat: ClockFormat
  showShieldsStats: boolean
  shieldsStats: ShieldsStats | null
  showTalkWidget: boolean
  talkFeatureEnabled: boolean
  newsFeatureEnabled: boolean
  aiChatInputEnabled: boolean
  centerNttCtaButtonFeatureEnabled: boolean
  actions: NewTabActions
}

export type NewTabStore = StateStore<NewTabState>

export function defaultNewTabStore(): NewTabStore {
  return createStateStore<NewTabState>({
    initialized: false,
    showClock: false,
    clockFormat: ClockFormat.kAuto,
    showShieldsStats: false,
    shieldsStats: null,
    showTalkWidget: false,
    talkFeatureEnabled: false,
    newsFeatureEnabled: false,
    aiChatInputEnabled: false,
    centerNttCtaButtonFeatureEnabled: false,
    actions: {
      setShowClock(showClock) {},
      setClockFormat(format) {},
      setShowShieldsStats(showShieldsStats) {},
      setShowTalkWidget(showTalkWidget) {},
    },
  })
}

export interface NewTabActions {
  setShowClock: (showClock: boolean) => void
  setClockFormat: (format: ClockFormat) => void
  setShowShieldsStats: (showShieldsStats: boolean) => void
  setShowTalkWidget: (showTalkWidget: boolean) => void
}
