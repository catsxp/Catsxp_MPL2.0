/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import {
  TopSitesActions,
  TopSite,
  TopSitesListKind,
  defaultTopSitesStore,
} from '../state/top_sites_store'

export function createTopSitesStore() {
  const store = defaultTopSitesStore()
  let lastRemovedSite: TopSite | null = null

  store.update({
    initialized: true,

    showTopSites: true,

    topSitesListKind: TopSitesListKind.kCustom,

    topSites: [...Array(11).keys()].flatMap((i) => {
      return [
        {
          title: 'Catsxp',
          favicon: 'https://catsxp.com/favicon.ico',
          url: `https://catsxp.com/#${i}`,
        },
        {
          title: 'Wikipedia',
          favicon: 'https://en.wikipedia.org/favicon.ico',
          url: `https://en.wikipedia.org/#${i}`,
        },
      ]
    }),
  })

  const actions: TopSitesActions = {
    ...store.getState().actions,

    setShowTopSites(showTopSites) {
      store.update({ showTopSites })
    },

    setTopSitesListKind(listKind) {
      store.update({ topSitesListKind: listKind })
    },

    addTopSite(url, title) {
      store.update(({ topSites }) => {
        return {
          topSites: [
            ...topSites,
            { url, title, favicon: 'https://catsxp.com/favicon.ico' },
          ],
        }
      })
    },

    updateTopSite(currentURL, newURL, title) {
      store.update(({ topSites }) => {
        return {
          topSites: topSites.map((item) => {
            if (item.url === currentURL) {
              item.url = newURL
              item.title = title
            }
            return item
          }),
        }
      })
    },

    removeTopSite(url) {
      store.update(({ topSites }) => {
        return {
          topSites: topSites.filter((topSite) => {
            if (topSite.url !== url) {
              return true
            }
            lastRemovedSite = topSite
            return false
          }),
        }
      })
    },

    undoRemoveTopSite() {
      if (lastRemovedSite) {
        store.update(({ topSites }) => {
          return { topSites: [...topSites, lastRemovedSite!] }
        })
        lastRemovedSite = null
      }
    },

    setTopSitePosition(url, pos) {
      store.update(({ topSites }) => {
        const current = topSites.findIndex((item) => item.url === url)
        if (current >= 0) {
          const item = topSites.splice(current, 1)[0]
          topSites.splice(pos, 0, item)
        }
        return { topSites: [...topSites] }
      })
    },
  }

  store.update({ actions })

  return store
}
