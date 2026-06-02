/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Button from '@catsxp/leo/react/button'

import { formatString } from '$web-common/formatString'
import { useShieldsApi } from '../api/shields_api_context'
import { getString } from './strings'
import { OpenTabLink } from './open_tab_link'
import { style } from './footer.style'

export function Footer() {
  const api = useShieldsApi()
  const { data: siteBlockInfo } = api.useGetSiteBlockInfo()
  const showAdvancedView = api.useGetAdvancedViewEnabledData()

  if (!siteBlockInfo) {
    return null
  }

  const shieldsEnabled = siteBlockInfo.isCatsxpShieldsEnabled
  const adblockOnlyEnabled = siteBlockInfo.isCatsxpShieldsAdBlockOnlyModeEnabled

  function renderActions() {
    if (shieldsEnabled && !showAdvancedView && !adblockOnlyEnabled) {
      return null
    }
    return (
      <div className='actions'>
        <Button
          kind='outline'
          onClick={() => api.openTab('chrome://settings/shields/filters')}
        >
          {getString('CATSXP_SHIELDS_CUSTOMIZE_ADBLOCK_LISTS')}
        </Button>
        <Button
          kind='outline'
          onClick={() => api.openTab('chrome://settings/shields')}
        >
          {getString('CATSXP_SHIELDS_GLOBAL_SETTINGS')}
        </Button>
      </div>
    )
  }

  function renderTryShieldsOffMessage() {
    if (!shieldsEnabled) {
      return null
    }
    return (
      <div className='try-off'>
        <p>{getString('CATSXP_SHIELDS_BROKEN')}</p>
        <p>
          {formatString(getString('CATSXP_SHIELDS_PRIVACY_NOTE'), {
            $1: (content) => (
              <OpenTabLink url='https://catsxp.com/privacy-features/'>
                {content}
              </OpenTabLink>
            ),
          })}
        </p>
      </div>
    )
  }

  return (
    <div data-css-scope={style.scope}>
      {renderActions()}
      {renderTryShieldsOffMessage()}
    </div>
  )
}
