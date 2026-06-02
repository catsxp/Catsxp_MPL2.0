/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { CatsxpNewsContextProvider } from '../../../../components/catsxp_news/browser/resources/shared/Context'
import { useNewTabState } from './new_tab_context'

export function NewsProvider(props: { children: React.ReactNode }) {
  const newsFeatureEnabled = useNewTabState((s) => s.newsFeatureEnabled)
  if (!newsFeatureEnabled) {
    return <>{props.children}</>
  }
  return <CatsxpNewsContextProvider>{props.children}</CatsxpNewsContextProvider>
}
