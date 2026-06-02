/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { SearchActions, defaultSearchStore } from '../state/search_store'

export function createSearchStore() {
  const store = defaultSearchStore()

  store.update({
    initialized: true,

    searchFeatureEnabled: true,

    showChatInput: true,
    showSearchBox: true,

    searchSuggestionsEnabled: false,

    searchSuggestionsPromptDismissed: false,

    searchEngines: [
      {
        prepopulateId: BigInt(0),
        name: 'Catsxp',
        keyword: '',
        host: 'search.catsxp.com',
        faviconUrl: '',
      },
      {
        prepopulateId: BigInt(1),
        name: 'Google',
        keyword: '',
        host: 'google.com',
        faviconUrl: '',
      },
    ],

    enabledSearchEngines: new Set(['search.catsxp.com', 'google.com']),
  })

  const actions: SearchActions = {
    ...store.getState().actions,

    setShowSearchBox(showSearchBox) {
      store.update({ showSearchBox })
    },

    setSearchSuggestionsEnabled(enabled) {
      store.update({ searchSuggestionsEnabled: enabled })
    },

    setSearchSuggestionsPromptDismissed(dismissed) {
      store.update({ searchSuggestionsPromptDismissed: dismissed })
    },

    setLastUsedSearchEngine(engine) {
      store.update({ lastUsedSearchEngine: engine })
    },

    setSearchEngineEnabled(engine, enabled) {
      store.update(({ enabledSearchEngines }) => {
        enabledSearchEngines = new Set(enabledSearchEngines)
        if (enabled) {
          enabledSearchEngines.add(engine)
        } else if (enabledSearchEngines.size > 1) {
          enabledSearchEngines.delete(engine)
        }
        return { enabledSearchEngines }
      })
    },

    setActiveSearchInputKey(key) {
      const { activeSearchInputKey } = store.getState()
      if (key !== activeSearchInputKey) {
        store.update({
          activeSearchInputKey: key,
          searchMatches: [],
        })
      }
    },

    queryAutocomplete(query, engine) {
      store.update({
        searchMatches: [
          {
            allowedToBeDefaultMatch: false,
            contents: 'contents 1',
            description: 'description 1',
            iconUrl: '',
            imageUrl: '',
            destinationUrl: '',
          },
          {
            allowedToBeDefaultMatch: true,
            contents: 'contents 2',
            description: 'Ask Leo',
            iconUrl: '',
            imageUrl: '',
            destinationUrl: '',
          },
          {
            allowedToBeDefaultMatch: true,
            contents: query,
            description: engine,
            iconUrl: '',
            imageUrl: '',
            destinationUrl: '',
          },
        ],
      })
    },

    setShowChatInput(showChatInput) {
      store.update({ showChatInput })
    },

    stopAutocomplete() {
      store.update({ searchMatches: [] })
    },
  }

  store.update({ actions })

  return store
}
