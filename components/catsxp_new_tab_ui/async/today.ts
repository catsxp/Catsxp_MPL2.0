/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import getCatsxpNewsController, * as CatsxpNews from '../../catsxp_news/browser/resources/shared/api'
import { addFeedListener } from '../../catsxp_news/browser/resources/shared/feedListener'
import AsyncActionHandler from '../../common/AsyncActionHandler'
import * as Actions from '../actions/today_actions'
import { ApplicationState } from '../reducers'
import store from '../store'

addFeedListener((hash) => {
  const current = store.getState().today.feed?.hash
  store.dispatch(Actions.isUpdateAvailable({ isUpdateAvailable: current !== hash }))
})

function storeInHistoryState (data: object) {
  const oldHistoryState =
    typeof history.state === 'object' ? history.state : {}
  const newHistoryState = { ...oldHistoryState, ...data }
  history.pushState(newHistoryState, document.title)
}

const handler = new AsyncActionHandler()

handler.on<Actions.RefreshPayload>(
  Actions.refresh.getType(),
  async (store) => {
    try {
      console.debug('Catsxp News: Getting data...')
      const [{ feed }, { publishers }] = await Promise.all([
        getCatsxpNewsController().getFeed(),
        getCatsxpNewsController().getPublishers()
      ])
      console.debug('Catsxp News: ...data received.')
      store.dispatch(Actions.dataReceived({ feed, publishers }))
    } catch (e) {
      console.error('error receiving feed', e)
      store.dispatch(Actions.errorGettingDataFromBackground(e))
    }
  }
)

handler.on(Actions.ensureSettingsData.getType(), async (store) => {
  const state = store.getState() as ApplicationState
  if (state.today.publishers && Object.keys(state.today.publishers).length) {
    return
  }
  const { publishers } = await getCatsxpNewsController().getPublishers()
  store.dispatch(Actions.dataReceived({ publishers }))
})

handler.on<Actions.ReadFeedItemPayload>(
  Actions.readFeedItem.getType(),
  async (store, payload) => {
    const state = store.getState() as ApplicationState
    const data =
      payload.item.article?.data ||
      payload.item.deal?.data
    if (!data) {
      console.error(
        'Catsxp News: readFeedItem payload item not present',
        payload
      )
      return
    }
    if (!payload.openInNewTab) {
      // remember article so we can scroll to it on "back" navigation
      // TODO(petemill): Type this history.state data and put in an API module
      // (see `reducers/today`).
      storeInHistoryState({
        todayArticle: data,
        todayPageIndex: state.today.currentPageIndex,
        todayCardsVisited: state.today.cardsVisited
      })
      // visit article url
      window.location.href = data.url.url
    } else {
      window.open(data.url.url, '_blank', 'noreferrer')
    }
  }
)

handler.on<number>(
  Actions.feedItemViewedCountChanged.getType(),
  async (store, payload) => {
    const state = store.getState() as ApplicationState
    getCatsxpNewsController().onNewCardsViewed(
      state.today.cardsViewedDelta
    )
  }
)

handler.on<Actions.RemoveDirectFeedPayload>(
  Actions.removeDirectFeed.getType(),
  async (store, payload) => {
    getCatsxpNewsController().removeDirectFeed(payload.directFeed.publisherId)
    window.setTimeout(() => {
      store.dispatch(Actions.checkForUpdate())
    }, 3000)
  }
)

handler.on<Actions.SetPublisherPrefPayload>(
  Actions.setPublisherPref.getType(),
  async (store, payload) => {
    const { publisherId, enabled } = payload
    let userStatus =
      enabled === null
        ? CatsxpNews.UserEnabled.NOT_MODIFIED
        : enabled
        ? CatsxpNews.UserEnabled.ENABLED
        : CatsxpNews.UserEnabled.DISABLED
    getCatsxpNewsController().setPublisherPref(publisherId, userStatus)
    // Refreshing of content after prefs changed is throttled, so wait
    // a while before seeing if we have new content yet.
    // This doesn't have to be exact since we often check for update when
    // opening or scrolling through the feed.
    window.setTimeout(() => {
      store.dispatch(Actions.checkForUpdate())
    }, 3000)
  }
)

handler.on(Actions.checkForUpdate.getType(), async function (store) {
  const state = store.getState() as ApplicationState
  // Detect if we did not get any data successfully and therefore we can try again
  // to fetch data
  if (!state.today.feed) {
    store.dispatch(Actions.isUpdateAvailable({ isUpdateAvailable: true }))
    return
  }
  const hash = state.today.feed.hash
  const isUpdateAvailable: { isUpdateAvailable: boolean } =
    await getCatsxpNewsController().isFeedUpdateAvailable(hash)
  store.dispatch(Actions.isUpdateAvailable(isUpdateAvailable))
})

handler.on(Actions.resetTodayPrefsToDefault.getType(), async function (store) {
  getCatsxpNewsController().clearPrefs()
  const { publishers } = await getCatsxpNewsController().getPublishers()
  store.dispatch(Actions.dataReceived({ publishers }))
  store.dispatch(Actions.checkForUpdate())
})

handler.on(Actions.anotherPageNeeded.getType(), async function (store) {
  store.dispatch(Actions.checkForUpdate())
})

export default handler.middleware
