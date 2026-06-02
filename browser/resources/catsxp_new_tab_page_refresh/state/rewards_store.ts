/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { StateStore, createStateStore } from '$web-common/state_store'

import { ExternalWallet } from '../../../../components/catsxp_rewards/resources/shared/lib/external_wallet'
import { ProviderPayoutStatus } from '../../../../components/catsxp_rewards/resources/shared/lib/provider_payout_status'

export interface RewardsState {
  initialized: boolean
  rewardsFeatureEnabled: boolean
  showRewardsWidget: boolean
  rewardsEnabled: boolean
  rewardsExternalWallet: ExternalWallet | null
  rewardsBalance: number | null
  rewardsExchangeRate: number
  rewardsAdsViewed: number | null
  minEarningsPreviousMonth: number
  payoutStatus: Record<string, ProviderPayoutStatus>
  tosUpdateRequired: boolean
  actions: RewardsActions
}

export type RewardsStore = StateStore<RewardsState>

export function defaultRewardsStore(): RewardsStore {
  return createStateStore<RewardsState>({
    initialized: false,
    rewardsFeatureEnabled: false,
    showRewardsWidget: false,
    rewardsEnabled: false,
    rewardsExternalWallet: null,
    rewardsBalance: null,
    rewardsExchangeRate: 0,
    rewardsAdsViewed: null,
    minEarningsPreviousMonth: 0,
    payoutStatus: {},
    tosUpdateRequired: false,
    actions: {
      setShowRewardsWidget(showRewardsWidget) {},
      recordNewTabOnboardingClick() {},
    },
  })
}

export interface RewardsActions {
  setShowRewardsWidget: (showRewardsWidget: boolean) => void
  recordNewTabOnboardingClick: () => void
}
