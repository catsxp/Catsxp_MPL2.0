/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { createRoot } from 'react-dom/client'
import { setIconBasePath } from '@catsxp/leo/react/icon'

import { NewTabContext } from './context/new_tab_context'
import { BackgroundContext } from './context/background_context'
import { SearchContext } from './context/search_context'
import { TopSitesContext } from './context/top_sites_context'
import { NewsProvider } from './context/news_context'

import { createNewTabStore } from './state/browser_new_tab_store'
import { createBackgroundStore } from './state/browser_background_store'
import { createSearchStore } from './state/browser_search_store'
import { createTopSitesStore } from './state/browser_top_sites_store'

import { App } from './components/app'

setIconBasePath('chrome://resources/catsxp-icons')

function AppProvider(props: { children: React.ReactNode }) {
  const stores = React.useMemo(() => {
    return {
      newTab: createNewTabStore(),
      background: createBackgroundStore(),
      search: createSearchStore(),
      topSites: createTopSitesStore(),
    }
  }, [])

  React.useEffect(() => {
    Reflect.set(self, '_ntp', stores)
  }, [])

  return (
    <NewTabContext.Provider value={stores.newTab}>
      <BackgroundContext.Provider value={stores.background}>
        <SearchContext.Provider value={stores.search}>
          <TopSitesContext.Provider value={stores.topSites}>
            <NewsProvider>{props.children}</NewsProvider>
          </TopSitesContext.Provider>
        </SearchContext.Provider>
      </BackgroundContext.Provider>
    </NewTabContext.Provider>
  )
}

createRoot(document.getElementById('root')!).render(
  <AppProvider>
    <App />
  </AppProvider>,
)
