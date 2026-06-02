/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { defaultVpnStore } from '../state/vpn_store'
import { createUseStateHook } from '$web-common/state_store_hooks'

export const VpnContext = React.createContext(defaultVpnStore())

export const useVpnState = createUseStateHook(VpnContext)

export function useVpnActions() {
  return useVpnState((s) => s.actions)
}
