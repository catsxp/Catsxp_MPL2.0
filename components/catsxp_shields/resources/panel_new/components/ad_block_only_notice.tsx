/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Icon from '@catsxp/leo/react/icon'

import { useShieldsApi } from '../api/shields_api_context'
import { getString } from './strings'
import { OpenTabLink } from './open_tab_link'

import { style } from './ad_block_only_notice.style'

export function MaybeAdBlockOnlyNotice() {
  const api = useShieldsApi()
  const { data: siteBlockInfo } = api.useGetSiteBlockInfo()

  if (!siteBlockInfo) {
    return null
  }

  const shieldsEnabled = siteBlockInfo.isCatsxpShieldsEnabled
  const adblockOnlyEnabled = siteBlockInfo.isCatsxpShieldsAdBlockOnlyModeEnabled

  const showNotice = shieldsEnabled && adblockOnlyEnabled
  if (!showNotice) {
    return null
  }

  return (
    <div data-css-scope={style.scope}>
      <div>
        <div>{getString('CATSXP_SHIELDS_AD_BLOCK_ONLY_MODE_ENABLE_TITLE')}</div>
        <p>{getString('CATSXP_SHIELDS_AD_BLOCK_ONLY_MODE_ENABLE_DESC')}</p>
      </div>
      <OpenTabLink
        url='chrome://settings/shields'
        aria-label={getString('CATSXP_SHIELDS_OPEN_SETTINGS')}
      >
        <Icon name='launch' />
      </OpenTabLink>
    </div>
  )
}
