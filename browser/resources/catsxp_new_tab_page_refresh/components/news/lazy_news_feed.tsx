/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { useCatsxpNews } from '../../../../../components/catsxp_news/browser/resources/shared/Context'
import { useNewTabState } from '../../context/new_tab_context'

import { style } from './lazy_news_feed.style'

const NewsFeed = React.lazy(() => import('./news_feed'))

export function LazyNewsFeed() {
  const catsxpNews = useCatsxpNews()
  const newsFeatureEnabled = useNewTabState((s) => s.newsFeatureEnabled)
  const newsVisible = catsxpNews.isShowOnNTPPrefEnabled
  const renderNews =
    newsFeatureEnabled && (newsVisible || catsxpNews.customizePage)

  if (!renderNews) {
    return null
  }

  return (
    <div data-css-scope={style.scope}>
      <React.Suspense fallback={newsVisible && <div className='loading' />}>
        <NewsFeed />
      </React.Suspense>
    </div>
  )
}
