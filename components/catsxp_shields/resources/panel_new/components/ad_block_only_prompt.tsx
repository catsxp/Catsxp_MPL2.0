/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Button from '@catsxp/leo/react/button'

import { useShieldsApi } from '../api/shields_api_context'
import { getString } from './strings'
import { formatString } from '$web-common/formatString'

import { style } from './ad_block_only_prompt.style'

const learnMoreURL =
  'https://www.catsxp.com/hc/en-us/articles/38076796692109'

export function MaybeAdBlockOnlyPrompt() {
  const api = useShieldsApi()
  const { data: siteBlockInfo } = api.useGetSiteBlockInfo()
  const repeatedReloadsDetected = api.useRepeatedReloadsDetectedData()

  if (!siteBlockInfo) {
    return null
  }

  const shieldsEnabled = siteBlockInfo.isCatsxpShieldsEnabled
  const adblockOnlyEnabled = siteBlockInfo.isCatsxpShieldsAdBlockOnlyModeEnabled
  const showDisabledPrompt =
    siteBlockInfo.showShieldsDisabledAdBlockOnlyModePrompt

  if (!adblockOnlyEnabled) {
    const showForRepeatedReloads = shieldsEnabled && repeatedReloadsDetected
    const showForShieldsDisabled = !shieldsEnabled && showDisabledPrompt
    if (showForRepeatedReloads || showForShieldsDisabled) {
      return <AdBlockOnlyEnablePrompt />
    }
  }

  if (shieldsEnabled && adblockOnlyEnabled) {
    return <AdBlockOnlyFeedbackPrompt />
  }

  return null
}

function AdBlockOnlyEnablePrompt() {
  const api = useShieldsApi()
  const setShieldsEnabled = api.setCatsxpShieldsEnabled
  const setAdBlockOnlyModeEnabled = api.setCatsxpShieldsAdBlockOnlyModeEnabled
  const setAdBlockOnlyModePromptDismissed =
    api.setCatsxpShieldsAdBlockOnlyModePromptDismissed

  return (
    <div data-css-scope={style.scope}>
      <h4>
        {getString(
          'CATSXP_SHIELDS_ARE_YOU_EXPERIENCING_ISSUES_WITH_THIS_SITE_TITLE',
        )}
      </h4>
      <p>
        {formatString(
          getString(
            'CATSXP_SHIELDS_ARE_YOU_EXPERIENCING_ISSUES_WITH_THIS_SITE_DESC1',
          ),
          {
            $1: (content) => (
              <button onClick={() => api.openTab(learnMoreURL)}>
                {content}
              </button>
            ),
          },
        )}
      </p>
      <div className='actions'>
        <Button
          onClick={() => {
            setShieldsEnabled([true])
            setAdBlockOnlyModeEnabled([true])
          }}
        >
          {getString('CATSXP_SHIELDS_ENABLE_AD_BLOCK_ONLY_MODE')}
        </Button>
        <Button
          kind='plain'
          onClick={() => setAdBlockOnlyModePromptDismissed()}
        >
          {getString('CATSXP_SHIELDS_DISMISS_ALERT')}
        </Button>
      </div>
    </div>
  )
}

function AdBlockOnlyFeedbackPrompt() {
  const api = useShieldsApi()
  return (
    <div data-css-scope={style.scope}>
      <h4>
        {getString('CATSXP_SHIELDS_IS_THIS_SITE_WORKING_CORRECTLY_NOW_TITLE')}
      </h4>
      <p>
        {getString('CATSXP_SHIELDS_IS_THIS_SITE_WORKING_CORRECTLY_NOW_DESC')}
      </p>
      <div className='actions'>
        <Button onClick={api.closeUI}>
          {getString(
            'CATSXP_SHIELDS_IS_THIS_SITE_WORKING_CORRECTLY_NOW_LOOKS_GOOD',
          )}
        </Button>
        <Button
          kind='plain'
          onClick={api.openWebCompatWindow}
        >
          {getString(
            'CATSXP_SHIELDS_IS_THIS_SITE_WORKING_CORRECTLY_NOW_REPORT_SITE',
          )}
        </Button>
      </div>
    </div>
  )
}
