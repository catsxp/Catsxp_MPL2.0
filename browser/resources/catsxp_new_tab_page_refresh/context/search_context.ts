/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { defaultSearchStore } from '../state/search_store'
import { createUseStateHook } from '$web-common/state_store_hooks'

export const SearchContext = React.createContext(defaultSearchStore())

export const useSearchState = createUseStateHook(SearchContext)

export function useSearchActions() {
  return useSearchState((s) => s.actions)
}

// Returns the current autocomplete search result matches for the current search
// query. If the currently active search input key is not `inputKey`, then null
// is returned. Use this hook rather than accessing `searchMatches` directly.
//
// This hook (and the `activeSearchInputKey` state) was added to support rich
// NTT backgrounds that display a functional Catsxp Search search box for
// promotional purposes. Since the autocomplete interface only supports one
// search input on the page, the `activeSearchInputKey` provides a way for
// multiple search "boxes" to coexist on the page without using each other's
// autocomplete results. Any component that queries autocomplete should first
// call `setActiveSearchInputKey` on the SearchActions interface and then should
// use this hook to access autocomplete results.
export function useSearchMatches(inputKey: string) {
  const searchMatches = useSearchState((s) => s.searchMatches)
  const activeSearchInputKey = useSearchState((s) => s.activeSearchInputKey)
  if (inputKey !== activeSearchInputKey) {
    return null
  }
  return searchMatches
}
