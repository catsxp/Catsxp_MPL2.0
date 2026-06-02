/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { debounce } from '$web-common/debounce'

const keyName = 'adblock-data'

export const defaultState: AdBlock.State = {
  settings: {
    customFilters: '',
    regionalLists: [],
    listSubscriptions: [],
  },
}

export const load = (): AdBlock.State => {
  const data = window.localStorage.getItem(keyName)
  let state: AdBlock.State = defaultState
  if (data) {
    try {
      state = JSON.parse(data)
    } catch (e) {
      console.error('Could not parse local storage data: ', e)
    }
  }
  return state
}

export const debouncedSave = debounce((data: AdBlock.State) => {
  if (data) {
    window.localStorage.setItem(keyName, JSON.stringify(data))
  }
}, 50)
