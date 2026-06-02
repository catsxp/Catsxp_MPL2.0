/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import * as S from './style'
import { withKnobs, boolean, text } from '@storybook/addon-knobs'

import './locale'
import MainPanel from '../components/main-panel'
import TreeList from '../components/tree-list'
import ThemeProvider from '../../../../common/CatsxpCoreThemeProvider'
import DataContext from '../state/context'
import {
  AdBlockMode,
  FingerprintMode,
  CookieBlockMode,
  HttpsUpgradeMode,
  ContentSettingSource,
} from '../api/panel_browser_api'
import {
  ViewType
} from '../state/component_types'
import { getLocale } from '../../../../common/locale'

import '@catsxp/leo/tokens/css/variables.css'
import {
  ContentSetting
} from 'gen/components/content_settings/core/common/content_settings.mojom.m'

const LIST_JS = [
  { 'url': 'https://www.reddit.com/' },
  { 'url': 'https://www.redditstatic.com/desktop2x/AuthorHovercard~Reddit.ca2d5405cdd178092347.js' },
  { 'url': 'https://www.redditstatic.com/desktop2x/Chat~Governance~Reddit.f64af7713c3261596c7c.js' },
  { 'url': 'https://www.redditstatic.com/desktop2x/CollectionCommentsPage~CommentsPage~ModerationPages~PostCreation~ProfileComments~ProfileOverview~Pro~d39c0d57.a37d209138f811a78126.js' },
  { 'url': 'https://www.redditstatic.com/desktop2x/CollectionCommentsPage~CommentsPage~ModerationPages~ProfileComments~ProfileOverview~ProfilePrivate~R~969c2956.44543839280e344fe35c.js' },
  { 'url': 'https://www.redditstatic.com/desktop2x/Frontpage.25b06963dc7114d6d5e5.js' },
  { 'url': 'https://www.redditstatic.com/desktop2x/Governance~ModListing~Reddit~ReportFlow~Subreddit.dcc2d2bd4fa3a45348eb.js' },
  { 'url': 'https://www.redditstatic.com/desktop2x/Governance~ModListing~Reddit~Subreddit.3f168f79abf6d859d163.js' },
  { 'url': 'https://www.redditstatic.com/desktop2x/Governance~Reddit.e7882cd59d01f560d9ed.js' },
  { 'url': 'https://www.redditstatic.com/desktop2x/Governance~Reddit~Subreddit~reddit-components-BlankPost~reddit-components-ClassicPost~reddit-compone~3b56c92e.14312dc2a044d45449c9.js' },
  { 'url': 'https://www.redditstatic.com/desktop2x/ModListing~PostCreation~Reddit~StandalonePostPage~Subreddit.b725e7ecf5d621c30c53.js' },
  { 'url': 'https://www.redditstatic.com/desktop2x/PostCreation~Reddit~StandalonePostPage~SubredditTopContent~TopWeekPostsDiscoveryUnit~reddit-componen~2583c786.1cc84f65074a696c0941.js' },
  { 'url': 'https://www.redditstatic.com/desktop2x/PostCreation~Reddit~StandalonePostPage~Subreddit~reddit-components-ClassicPost~reddit-components-Com~82e48dd3.85bb0a8c6be58f085676.js' },
  { 'url': 'https://api.github.com/_private/browser/stats' }
]

const LIST_ADS = [
  { url: 'ads.catsxp.com' },
  { url: 'ads2.catsxp.com' }
]

export default {
  title: 'ShieldsV2/Panels',
  parameters: {
    layout: 'centered'
  },
  argTypes: {
    locked: { control: { type: 'boolean', lock: false } }
  },
  decorators: [
    (Story: any) => {
      // mock data
      const store = {
        siteBlockInfo: {
          host: text('Host name', 'catsxp.com'),
          totalBlockedResources: (LIST_ADS.length + LIST_JS.length),
          isCatsxpShieldsEnabled: boolean('Enable Shields', true),
          isCatsxpShieldsAdBlockOnlyModeEnabled: boolean('Enable Shields Adblock-Only Mode', false),
          showShieldsDisabledAdBlockOnlyModePrompt: boolean('Show Shields Disabled Adblock-Only Mode Prompt', false),
          isCatsxpShieldsManaged: boolean('Shields Managed', false),
          adsList: LIST_ADS,
          blockedJsList: LIST_JS,
          allowedJsList: LIST_JS,
          httpRedirectsList: [],
          fingerprintsList: [],
          faviconUrl: { url: 'https://catsxp.com/static-assets/images/catsxp-favicon.png' },
          invokedWebcompatList: []
        },
        siteSettings: {
          adBlockMode: AdBlockMode.ALLOW,
          fingerprintMode: FingerprintMode.ALLOW_MODE,
          cookieBlockMode: CookieBlockMode.ALLOW,
          httpsUpgradeMode: HttpsUpgradeMode.DISABLED_MODE,
          isNoscriptEnabled: false,
          scriptsBlockedOverrideStatus: {
            status: ContentSetting.DEFAULT,
            overrideSource: ContentSettingSource.kNone,
          },
          isForgetFirstPartyStorageEnabled: false,
          webcompatSettings: {}
        },
        viewType: ViewType.Main
      }

      return (
        <DataContext.Provider value={store}>
          <ThemeProvider>
            <Story />
          </ThemeProvider>
        </DataContext.Provider>
      )
    },
    withKnobs
  ]
}

export const _Main = {
  render: () => {
    return (
      <S.PanelFrame>
        <MainPanel />
      </S.PanelFrame>
    )
  }
}

export const _ResourceList = {
  render: () => {
    const { siteBlockInfo } = React.useContext(DataContext)

    if (!siteBlockInfo) {
      return
    }

    return (
      <S.PanelFrame>
        <TreeList
          blockedList={siteBlockInfo?.blockedJsList}
          allowedList={siteBlockInfo?.allowedJsList}
          totalAllowedTitle={getLocale('catsxpShieldsAllowedScriptsLabel')}
          totalBlockedTitle={getLocale('catsxpShieldsBlockedScriptsLabel')}
        />
      </S.PanelFrame>
    )
  }
}
