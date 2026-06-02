/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { ViewType, Scenes } from './component_types'
import { BrowserProfile } from '../api/welcome_browser_proxy'

export interface Store {
  setViewType: (viewType: ViewType) => void
  setCurrentSelectedBrowser: (currentSelection: string) => void
  incrementCount: () => void
  setScenes: React.Dispatch<React.SetStateAction<Scenes | undefined>>
  currentSelectedBrowser: string | undefined
  browserProfiles: BrowserProfile[] | undefined
  currentSelectedBrowserProfiles: BrowserProfile[] | undefined
  viewType: ViewType | undefined
  scenes: Scenes | undefined
}

const defaultStore = {
  setViewType: () => {},
  setCurrentSelectedBrowser: () => {},
  incrementCount: () => {},
  setScenes: () => {},
  currentSelectedBrowser: undefined,
  browserProfiles: undefined,
  currentSelectedBrowserProfiles: undefined,
  viewType: undefined,
  scenes: undefined,
  countryString: undefined,
}

const DataContext = React.createContext<Store>(defaultStore)

export default DataContext
