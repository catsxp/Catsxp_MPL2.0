/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import {
  defaultBackgroundStore,
  getCurrentBackground,
} from '../state/background_store'
import { createUseStateHook } from '$web-common/state_store_hooks'

export const BackgroundContext = React.createContext(defaultBackgroundStore())

export const useBackgroundState = createUseStateHook(BackgroundContext)

export function useBackgroundActions() {
  return useBackgroundState((s) => s.actions)
}

export function useCurrentBackground() {
  const state = useBackgroundState((s) => ({ ...s }))
  return React.useMemo(() => getCurrentBackground(state), Object.values(state))
}
