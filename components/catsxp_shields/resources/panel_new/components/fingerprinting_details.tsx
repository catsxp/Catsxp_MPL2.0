/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Toggle from '@catsxp/leo/react/toggle'

import { getString } from './strings'
import { ContentSettingsType } from 'gen/components/content_settings/core/common/content_settings_types.mojom.m'
import { useShieldsApi } from '../api/shields_api_context'
import { DetailsHeader } from './details_header'

import { style } from './fingerprinting_details.style'

const learnMoreUrl =
  'https://www.catsxp.com/hc/en-us/articles/360022806212-How-do-I-use-Shields-while-browsing#h_01HXSZ8JPHR8YMBEZCT5M0VZTR'

const webcompatSettingNames = new Map(
  Object.entries(ContentSettingsType)
    .filter(([key, value]) => {
      return (
        value > ContentSettingsType.CATSXP_WEBCOMPAT_NONE
        && value < ContentSettingsType.CATSXP_WEBCOMPAT_ALL
      )
    })
    .map(([key, value]) => {
      const name = key
        .replace('CATSXP_WEBCOMPAT_', '')
        .replaceAll('_', ' ')
        .toLowerCase()
      return [value, name]
    }),
)

interface Props {
  onBack: () => void
}

export function FingerprintingDetails(props: Props) {
  const api = useShieldsApi()
  const { data: siteBlockInfo } = api.useGetSiteBlockInfo()
  const { data: siteSettings } = api.useGetSiteSettings()

  const invokedList = siteBlockInfo?.invokedWebcompatList ?? []
  const webcompatSettings = siteSettings?.webcompatSettings ?? []

  // Build the list of toggles that will be displayed from invokedWebcompatList.
  // Note that the toggle is *on* if the webcompat setting is *off*. (Enabling
  // the webcompat setting disables the fingerprinting protection.)
  const entries = React.useMemo(() => {
    return invokedList
      .map((value) => ({
        name: webcompatSettingNames.get(value) ?? '',
        value,
        enabled: !webcompatSettings[value],
      }))
      .filter((entry) => entry.name)
  }, [invokedList, webcompatSettings])

  if (!siteBlockInfo || !siteSettings) {
    return null
  }

  const enabledCount = entries.filter((entry) => entry.enabled).length

  const title = getString('CATSXP_SHIELDS_FINGERPRINTING_PROTECTIONS_TITLE')

  return (
    <main data-css-scope={style.scope}>
      <DetailsHeader
        title={`${title} (${enabledCount})`}
        onBack={props.onBack}
      >
        <p className='header-text'>
          {getString('CATSXP_SHIELDS_FINGERPRINTING_LIST_DESCRIPTION')}{' '}
          <button onClick={() => api.openTab(learnMoreUrl)}>
            {getString('CATSXP_SHIELDS_LEARN_MORE_LINK_TEXT')}
          </button>
        </p>
      </DetailsHeader>
      <div className='toggle-list scrollable'>
        {entries.map((entry) => (
          <div key={entry.value}>
            {entry.name}
            <Toggle
              size='small'
              checked={entry.enabled}
              onChange={(event) => {
                api.setWebcompatEnabled([entry.value, !event.checked])
              }}
            />
          </div>
        ))}
      </div>
    </main>
  )
}
