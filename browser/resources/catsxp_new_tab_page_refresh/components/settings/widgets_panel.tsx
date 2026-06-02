/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Toggle from '@catsxp/leo/react/toggle'

import { useCatsxpNews } from '../../../../../components/catsxp_news/browser/resources/shared/Context'

import { getString } from '../../lib/strings'
import { useNewTabState, useNewTabActions } from '../../context/new_tab_context'

import { style } from './widgets_panel.style'

export function WidgetsPanel() {
  const catsxpNews = useCatsxpNews()
  const newTabActions = useNewTabActions()

  const showStats = useNewTabState((s) => s.showShieldsStats)
  const newsFeatureEnabled = useNewTabState((s) => s.newsFeatureEnabled)

  return (
    <div data-css-scope={style.scope}>
      <Toggle
        className='toggle-row'
        size='small'
        checked={showStats}
        onChange={({ checked }) => {
          newTabActions.setShowShieldsStats(checked)
        }}
      >
        <span className='label'>{getString(S.NEW_TAB_SHOW_STATS_LABEL)}</span>
      </Toggle>
      {newsFeatureEnabled && (
        <Toggle
          className='toggle-row'
          size='small'
          checked={catsxpNews.isShowOnNTPPrefEnabled}
          onChange={({ checked }) => {
            catsxpNews.toggleCatsxpNewsOnNTP(checked)
          }}
        >
          <span className='label'>
            {getString(S.NEW_TAB_SHOW_NEWS_WIDGET_LABEL)}
          </span>
        </Toggle>
      )}
    </div>
  )
}
