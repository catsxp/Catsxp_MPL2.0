/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { boolean } from '@storybook/addon-knobs'
import { CatsxpNewsState } from '../../../reducers/today'
import { feed, publishers } from './mockCatsxpNewsController'

export default function getTodayState (): CatsxpNewsState {
  const hasDataError = boolean('Today data fetch error?', false)
  return {
    isFetching: boolean('Today is fetching?', false),
    hasInteracted: boolean('Today has interacted?', false),
    isUpdateAvailable: boolean('Is Today update available?', false),
    currentPageIndex: 10,
    cardsViewed: 0,
    cardsViewedDelta: 0,
    cardsVisited: 0,
    publishers: hasDataError ? undefined : publishers,
    feed: hasDataError ? undefined : feed
  }
}
