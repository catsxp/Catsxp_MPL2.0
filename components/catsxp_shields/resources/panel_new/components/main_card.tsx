/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Button from '@catsxp/leo/react/button'
import Toggle from '@catsxp/leo/react/toggle'

import { formatString } from '$web-common/formatString'
import { useShieldsApi } from '../api/shields_api_context'
import { getString } from './strings'

import { style } from './main_card.style'

export function MainCard() {
  const api = useShieldsApi()
  const { data: siteBlockInfo } = api.useGetSiteBlockInfo()

  if (!siteBlockInfo) {
    return null
  }

  const favicon = siteBlockInfo.faviconUrl.url
  const siteHost = siteBlockInfo.host
  const shieldsEnabled = siteBlockInfo.isCatsxpShieldsEnabled
  const trackersAndAdsBlocked = siteBlockInfo.totalBlockedResources

  function renderBlockInfo() {
    if (!shieldsEnabled) {
      return (
        <div className='report-prompt'>
          {getString('CATSXP_SHIELDS_SITE_NOT_WORKING')}
          <Button onClick={api.openWebCompatWindow}>
            {getString('CATSXP_SHIELDS_REPORT')}
          </Button>
        </div>
      )
    }
    return (
      <div className='block-info'>
        <div className='blocked-items' />
        {formatString(getString('CATSXP_SHIELDS_TRACKERS_ADS_BLOCKED'), {
          $1: () => <div className='count'>{trackersAndAdsBlocked}</div>,
        })}
      </div>
    )
  }

  return (
    <div
      data-css-scope={style.scope}
      data-shields-off={!shieldsEnabled}
    >
      <div className='site-info'>
        <div className='site-icon'>
          {favicon && (
            <img
              src={favicon}
              alt={siteHost}
            />
          )}
        </div>
        <div className='site-text'>
          <h3
            className='overflow-ellipsis-start'
            title={siteHost}
          >
            {'\u2068'}
            {siteHost}
            {'\u2069'}
          </h3>
          <div className='shields-status'>
            {formatString(
              shieldsEnabled
                ? getString('CATSXP_SHIELDS_STATUS_UP')
                : getString('CATSXP_SHIELDS_STATUS_DOWN'),
              {
                $1: (content) => <strong>{content}</strong>,
              },
            )}
          </div>
        </div>
        <Toggle
          checked={shieldsEnabled}
          onChange={(event) => api.setCatsxpShieldsEnabled([event.checked])}
        />
      </div>
      {renderBlockInfo()}
    </div>
  )
}
