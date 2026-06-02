/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { useShieldsApi } from '../api/shields_api_context'
import { getString } from './strings'
import { DetailsHeader } from './details_header'
import { ResourceListView } from './resource_list_view'

import { style } from './ads_blocked_details.style'

interface Props {
  onBack: () => void
}

export function AdsBlockedDetails(props: Props) {
  const api = useShieldsApi()
  const { data: siteBlockInfo } = api.useGetSiteBlockInfo()
  const adsList = siteBlockInfo?.adsList ?? []
  const title = getString('CATSXP_SHIELDS_TRACKERS_ADS_BLOCKED_TITLE')
  return (
    <main data-css-scope={style.scope}>
      <DetailsHeader
        title={`${title} (${adsList.length})`}
        onBack={props.onBack}
      />
      <div className='resource-list scrollable'>
        <ResourceListView urls={adsList.map((url) => url.url)} />
      </div>
    </main>
  )
}
