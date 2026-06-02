/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { useDispatch } from 'react-redux'
import * as CatsxpNews from '../../../../catsxp_news/browser/resources/shared/api'
import * as TodayActions from '../../../actions/today_actions'
import { useNewTabPref } from '../../../hooks/usePref'
import { defaultState } from '../../../storage/new_tab_storage'
import CardLoading from './cards/cardLoading'
import CardOptIn from '../../../../catsxp_news/browser/resources/OptIn'
import * as CatsxpNewsElement from './default'

const Content = React.lazy(() => import('./content'))
const FeedV2 = React.lazy(() => import('../../../../catsxp_news/browser/resources/Page'))

// When FeedV2 is enabled, immediately start loading the Catsxp News chunk,
// rather than waiting for the parent component to render.
if (defaultState.featureFlagCatsxpNewsFeedV2Enabled) {
  import('../../../../catsxp_news/browser/resources/Page')
}

export type OnReadFeedItem = (args: TodayActions.ReadFeedItemPayload) => any
export type OnSetPublisherPref = (publisherId: string, enabled: boolean) => any
export type Props = {
  isFetching: boolean
  hasInteracted: boolean
  isUpdateAvailable: boolean
  isPrompting: boolean
  feed?: CatsxpNews.Feed
  publishers?: CatsxpNews.Publishers
  articleToScrollTo?: CatsxpNews.FeedItemMetadata
  displayedPageCount: number
  onReadFeedItem: OnReadFeedItem
  onFeedItemViewedCountChanged: (feedItemsViewed: number) => any
  onSetPublisherPref: OnSetPublisherPref
  onAnotherPageNeeded: () => any
  onCustomizeCatsxpNews: () => any
  onRefresh: () => any
  onCheckForUpdate: () => any
}

type PossibleInteractionObserver = IntersectionObserver | undefined

export const attributeNameCardCount = 'data-today-card-count'

const intersectionOptions = { root: null, rootMargin: '0px', threshold: 0.25 }

export default function CatsxpNewsSection(props: Props) {
  const dispatch = useDispatch()
  const [optedIn] = useNewTabPref('isCatsxpNewsOptedIn')

  // Don't ask for initial data more than once
  const hasRequestedLoad = React.useRef(false)

  const loadDataObserver = React.useMemo<PossibleInteractionObserver>(() => {
    // Handle case where we're already told to load content, e.g. when
    // navigating back to a position in the feed after clicking an article
    // or ad.
    if (props.hasInteracted) {
      dispatch(TodayActions.refresh({ isFirstInteraction: false }))
      hasRequestedLoad.current = true
      return
    }
    // Handle case where we wait for News content area to hit viewport
    // before lazy-loading content.
    const handleHits: IntersectionObserverCallback = (entries) => {
      // When the scroll trigger hits the viewport (or is above the viewport),
      // we can start to fetch data.
      const isIntersecting = entries.some(entry => entry.isIntersecting)
      if (isIntersecting && !hasRequestedLoad.current) {
        // Only send interaction event when we're not loading data simply because
        // we're promoting items. In that case, the interaction event will
        // be sent by the content component when the content is first interacted
        // with.
        const shouldMarkInteraction = !props.isPrompting
        console.debug('Catsxp News: section is in position that requires requesting data load')
        dispatch(TodayActions.refresh({ isFirstInteraction: shouldMarkInteraction }))
        hasRequestedLoad.current = true
      }
    }
    // Setup intersection observer params
    return new IntersectionObserver(handleHits, intersectionOptions)
  }, [props.isPrompting, props.hasInteracted])

  const loadDataTrigger = React.useRef<HTMLDivElement>(null)

  React.useEffect(() => {
    // When we have an element to observe, set it as the target.
    // Don't do anything if we don't need data.
    if (!loadDataObserver ||
      !loadDataTrigger.current ||
      !optedIn ||
      !!props.feed) {
      return
    }
    loadDataObserver.observe(loadDataTrigger.current)
    return () => {
      // Cleanup current observer if we get a new observer, or a new element to observe
      loadDataObserver.disconnect()
    }
  }, [loadDataObserver, loadDataTrigger.current, optedIn, !!props.feed])

  // Only load all the content DOM elements if we're
  // scrolled far down enough, otherwise it's too easy to scroll down
  // by accident and get all the elements added.
  // Also sanity check isOptedIn, but without it there shouldn't be any content
  // anyway.
  const shouldDisplayContent = optedIn &&
    (props.hasInteracted || props.isPrompting)

  return (
    <CatsxpNewsElement.Section>
      <div
        ref={loadDataTrigger}
        style={{ position: 'sticky', top: '100px' }}
      />
      {!optedIn && <CardOptIn />}
      {shouldDisplayContent && <React.Suspense fallback={defaultState.featureFlagCatsxpNewsFeedV2Enabled ? null : <CardLoading />}>
        {defaultState.featureFlagCatsxpNewsPromptEnabled
          && (defaultState.featureFlagCatsxpNewsFeedV2Enabled
            ? <FeedV2 />
            : <Content {...props} />)}
      </React.Suspense>}

    </CatsxpNewsElement.Section>
  )
}
