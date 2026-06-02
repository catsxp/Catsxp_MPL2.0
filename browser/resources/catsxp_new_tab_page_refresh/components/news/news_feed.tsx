/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { useCatsxpNews } from '../../../../../components/catsxp_news/browser/resources/shared/Context'
import OptIn from '../../../../../components/catsxp_news/browser/resources/OptIn'
import NewsPage from '../../../../../components/catsxp_news/browser/resources/Page'
import CustomizeModal from '../../../../../components/catsxp_news/browser/resources/customize/Modal'
import { useNewTabState } from '../../context/new_tab_context'

import { style } from './news_feed.style'

export function NewsFeed() {
  const catsxpNews = useCatsxpNews()
  const newsFeatureEnabled = useNewTabState((s) => s.newsFeatureEnabled)
  const [shouldRenderNews, setShouldRenderNews] = React.useState(false)

  React.useEffect(() => {
    setTimeout(() => setShouldRenderNews(true), 1000)
  }, [])

  if (!newsFeatureEnabled) {
    return null
  }

  return (
    <>
      {catsxpNews.isShowOnNTPPrefEnabled && (
        <div data-css-scope={style.scope}>
          {catsxpNews.isOptInPrefEnabled ? (
            shouldRenderNews && <NewsPage />
          ) : (
            <OptIn />
          )}
        </div>
      )}
      {catsxpNews.customizePage && <CustomizeModal />}
    </>
  )
}

export default NewsFeed
