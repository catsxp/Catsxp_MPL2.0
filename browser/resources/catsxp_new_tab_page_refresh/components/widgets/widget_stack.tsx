/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Icon from '@catsxp/leo/react/icon'

import { useCatsxpNews } from '../../../../../components/catsxp_news/browser/resources/shared/Context'
import { useNewTabState } from '../../context/new_tab_context'
import { NtpWidget } from './ntp_widget'
import { StatsWidget } from './stats_widget'
import { NewsWidget } from './news_widget'

import { style } from './widget_stack.style'

type TabName = 'stats' | 'news'

interface Props {
  name: string
  tabs: TabName[]
}

export function WidgetStack(props: Props) {
  const showShieldsStats = useNewTabState((s) => s.showShieldsStats)
  const showNews = useCatsxpNews().isShowOnNTPPrefEnabled
  const newsFeatureEnabled = useNewTabState((s) => s.newsFeatureEnabled)

  const [currentTab, setCurrentTab] = React.useState(loadCurrentTab(props.name))

  const visibleTabs = React.useMemo(() => {
    return props.tabs.filter((tab) => {
      switch (tab) {
        case 'stats':
          return showShieldsStats
        case 'news':
          return newsFeatureEnabled && showNews
      }
    })
  }, [
    props.tabs,
    showShieldsStats,
    showNews,
    newsFeatureEnabled,
  ])

  function renderTabButton(tab: TabName) {
    return (
      <button
        key={tab}
        className={tab === activeTab ? 'active' : ''}
        data-testid={`${tab}-widget-tab`}
        onClick={() => {
          storeCurrentTab(props.name, tab)
          setCurrentTab(tab)
        }}
      >
        {renderProductIcon(tab)}
      </button>
    )
  }

  function renderProductIcon(tab: TabName) {
    switch (tab) {
      case 'stats':
        return <Icon name='bar-chart' />
      case 'news':
        return <Icon name='product-catsxp-news' />
    }
  }

  function renderWidget() {
    switch (activeTab) {
      case 'stats':
        return <StatsWidget />
      case 'news':
        return <NewsWidget />
    }
  }

  if (visibleTabs.length === 0) {
    return null
  }

  const activeTab =
    currentTab && visibleTabs.includes(currentTab) ? currentTab : visibleTabs[0]

  return (
    <NtpWidget>
      <div data-css-scope={style.scope}>
        {visibleTabs.length > 1 && (
          <div className='stack-tabs'>{visibleTabs.map(renderTabButton)}</div>
        )}
        <div className='widget'>{renderWidget()}</div>
      </div>
    </NtpWidget>
  )
}

function loadCurrentTab(stackName: string): TabName | null {
  const value = localStorage.getItem(storageKey(stackName))
  return tabNameIdentity(value as TabName) ?? null
}

function tabNameIdentity(tabName: TabName): TabName {
  switch (tabName) {
    case 'stats':
    case 'news':
      return tabName
  }
}

function storeCurrentTab(stackName: string, tab: TabName | null) {
  localStorage.setItem(storageKey(stackName), tab ?? '')
}

function storageKey(stackName: string) {
  return `ntp-current-${stackName}-widget`
}
