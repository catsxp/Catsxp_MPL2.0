/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { NewTabActions, defaultNewTabStore } from '../state/new_tab_store'

export function createNewTabStore() {
  const store = defaultNewTabStore()
  store.update({
    initialized: true,
    showClock: true,
    showShieldsStats: true,

    shieldsStats: {
      adsBlocked: 3245,
      bandwidthSavedBytes: 1024 * 1024,
    },
    showTalkWidget: true,
    talkFeatureEnabled: true,
    newsFeatureEnabled: false,
    aiChatInputEnabled: true,
  })

  const actions: NewTabActions = {
    ...store.getState().actions,

    setClockFormat(format) {
      store.update({ clockFormat: format })
    },

    setShowClock(showClock) {
      store.update({ showClock })
    },

    setShowShieldsStats(showShieldsStats) {
      store.update({ showShieldsStats })
    },

    setShowTalkWidget(showTalkWidget) {
      store.update({ showTalkWidget })
    },
  }

  store.update({ actions })

  return store
}
