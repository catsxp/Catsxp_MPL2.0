/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Icon from '@catsxp/leo/react/icon'

import { useShieldsApi } from '../api/shields_api_context'
import { getString } from './strings'

import { style } from './advanced_settings_header.style'

export function AdvancedSettingsHeader() {
  const api = useShieldsApi()
  const { data: siteBlockInfo } = api.useGetSiteBlockInfo()
  const showAdvancedView = api.useGetAdvancedViewEnabledData()

  if (!siteBlockInfo) {
    return null
  }

  const shieldsEnabled = siteBlockInfo.isCatsxpShieldsEnabled
  const adblockOnlyEnabled = siteBlockInfo.isCatsxpShieldsAdBlockOnlyModeEnabled

  if (!shieldsEnabled || adblockOnlyEnabled) {
    return null
  }

  return (
    <div
      data-css-scope={style.scope}
      data-expanded={showAdvancedView}
    >
      <button
        className='view-toggle'
        onClick={() => {
          api.setAdvancedViewEnabled([!showAdvancedView])
        }}
      >
        <Icon name='settings' />
        <span>{getString('CATSXP_SHIELDS_ADVANCED_OPTIONS')}</span>
        <Icon name={showAdvancedView ? 'carat-up' : 'carat-down'} />
      </button>
    </div>
  )
}
