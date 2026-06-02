/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { defaultRewardsStore } from '../state/rewards_store'
import { createUseStateHook } from '$web-common/state_store_hooks'

export const RewardsContext = React.createContext(defaultRewardsStore())

export const useRewardsState = createUseStateHook(RewardsContext)

export function useRewardsActions() {
  return useRewardsState((s) => s.actions)
}
