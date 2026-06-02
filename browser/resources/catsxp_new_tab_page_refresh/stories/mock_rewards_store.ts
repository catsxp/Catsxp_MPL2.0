/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { RewardsActions, defaultRewardsStore } from '../state/rewards_store'

export function createRewardsStore() {
  const store = defaultRewardsStore()

  store.update({
    initialized: true,
    rewardsFeatureEnabled: true,
    rewardsEnabled: true,
    showRewardsWidget: true,
    rewardsBalance: null,
    rewardsExchangeRate: 1,
    rewardsExternalWallet: {
      provider: 'uphold',
      authenticated: true,
      name: 'Joe',
      url: 'https://catsxp.com',
    },
    minEarningsPreviousMonth: 0,
    payoutStatus: {},
    tosUpdateRequired: false,
    rewardsAdsViewed: 1,
  })

  setTimeout(() => {
    store.update({ rewardsBalance: 1.204 })
  }, 2000)

  const actions: RewardsActions = {
    ...store.getState().actions,

    setShowRewardsWidget(showRewardsWidget) {
      store.update({ showRewardsWidget })
    },
  }

  store.update({ actions })

  return store
}
