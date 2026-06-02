/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import MainPanel from './components/main-panel'
import TreeList, { ToggleList } from './components/tree-list'
import {
  ViewType
} from './state/component_types'
import DataContext from './state/context'
import styled from 'styled-components'
import { getLocale } from '../../../common/locale'

const Box = styled.div`
  position: relative;
`

function Container () {
  const { siteBlockInfo, viewType, siteSettings } = React.useContext(DataContext)
  const shouldShowDetailView = viewType !== ViewType.Main && siteBlockInfo

  let treeListElement = null
  if (shouldShowDetailView) {
    if (viewType === ViewType.AdsList) {
      treeListElement = <TreeList
        blockedList={siteBlockInfo?.adsList}
        totalBlockedTitle={getLocale('catsxpShieldsTrackersAndAds')}
      />
    }

    if (viewType === ViewType.HttpsList) {
      treeListElement = <TreeList
        blockedList={ siteBlockInfo?.httpRedirectsList }
        totalBlockedTitle={getLocale('catsxpShieldsConnectionsUpgraded')}
      />
    }

    if (viewType === ViewType.ScriptsList) {
      treeListElement = <TreeList
          blockedList={ siteBlockInfo?.blockedJsList }
          allowedList={ siteBlockInfo?.allowedJsList }
          totalAllowedTitle={getLocale('catsxpShieldsAllowedScriptsLabel')}
          totalBlockedTitle={getLocale('catsxpShieldsBlockedScriptsLabel')}
        />
    }

    if (viewType === ViewType.FingerprintList) {
      treeListElement = <ToggleList
          webcompatSettings={ siteSettings?.webcompatSettings }
          totalBlockedTitle={getLocale('catsxpShieldsFingerprintingProtectionsAppliedLabel')}
          learnMoreText={getLocale('catsxpShieldsLearnMoreLinkText')}
          listDescription={getLocale('catsxpShieldsFingerprintingListDescription')}
      />
    }
  }

  return (
    <Box>
      {treeListElement}
      <MainPanel />
    </Box>
  )
}

export default Container
