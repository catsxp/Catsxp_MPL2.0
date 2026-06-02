/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import type { Meta, StoryObj } from '@storybook/react'

import '../../../../components/catsxp_new_tab_ui/stories/default/data/mockCatsxpNewsController'

import { NewTabContext } from '../context/new_tab_context'
import { BackgroundContext } from '../context/background_context'
import { SearchContext } from '../context/search_context'
import { TopSitesContext } from '../context/top_sites_context'

import { createNewTabStore } from './mock_new_tab_store'
import {
  createBackgroundStore,
  updateSponsoredBackground,
} from './mock_background_store'
import { createSearchStore } from './mock_search_store'
import { createTopSitesStore } from './mock_top_sites_store'

import { StorybookArgs } from './storybook_args'

import { App } from '../components/app'

interface StorybookArgs {
  sponsoredBackgroundType: 'none' | 'image' | 'rich'
}

function StorybookApp(props: StorybookArgs) {
  const stores = React.useMemo(() => {
    return {
      newTab: createNewTabStore(),
      background: createBackgroundStore(),
      search: createSearchStore(),
      topSites: createTopSitesStore(),
    }
  }, [])

  React.useEffect(() => {
    updateSponsoredBackground(stores.background, props.sponsoredBackgroundType)
  }, [props.sponsoredBackgroundType])

  return (
    <NewTabContext.Provider value={stores.newTab}>
      <BackgroundContext.Provider value={stores.background}>
        <SearchContext.Provider value={stores.search}>
          <TopSitesContext.Provider value={stores.topSites}>
            <div style={{ position: 'absolute', inset: 0 }}>
              <App />
            </div>
          </TopSitesContext.Provider>
        </SearchContext.Provider>
      </BackgroundContext.Provider>
    </NewTabContext.Provider>
  )
}

export default {
  title: 'New Tab Page/App',
  component: StorybookApp,
} satisfies Meta<typeof StorybookApp>

export const NewTabPage: StoryObj<typeof StorybookApp> = {
  argTypes: {
    sponsoredBackgroundType: {
      control: 'select',
      options: ['none', 'image', 'rich'],
    },
  },
}
