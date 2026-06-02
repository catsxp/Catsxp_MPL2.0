/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { defaultNewTabStore } from '../state/new_tab_store'
import { createUseStateHook } from '$web-common/state_store_hooks'

export const NewTabContext = React.createContext(defaultNewTabStore())

export const useNewTabState = createUseStateHook(NewTabContext)

export function useNewTabActions() {
  return useNewTabState((s) => s.actions)
}
