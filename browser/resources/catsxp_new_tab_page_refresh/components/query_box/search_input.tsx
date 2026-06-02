/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Button from '@catsxp/leo/react/button'
import Icon from '@catsxp/leo/react/icon'

import { catsxpSearchHost } from '../../state/search_store'
import { getString } from '../../lib/strings'
import { SearchEnginePicker } from '../search/search_engine_picker'
import { SearchResults } from '../search/search_results'
import { useSearchInputState } from '../search/search_input_state'

import { style } from './search_input.style'

interface Props {
  showSearchSettings: () => void
  renderInputToggle?: () => React.ReactNode
}

export function SearchInput(props: Props) {
  const inputState = useSearchInputState('search-box')
  const engineHost = inputState.searchEngine?.host
  const inputRef = React.useRef<HTMLInputElement>(null)

  function focusInput() {
    inputRef.current?.focus()
  }

  return (
    <div
      data-css-scope={style.scope}
      data-testid='ntp-search-input'
    >
      <input
        ref={inputRef}
        autoFocus
        type='text'
        placeholder={
          engineHost === catsxpSearchHost
            ? getString(S.NEW_TAB_SEARCH_BOX_PLACEHOLDER_TEXT_CATSXP)
            : getString(S.NEW_TAB_SEARCH_BOX_PLACEHOLDER_TEXT)
        }
        value={inputState.query}
        onFocus={() => inputState.setActiveInput()}
        onKeyDown={(event) => {
          inputState.handleActionKeyDown(event.nativeEvent)
        }}
        onChange={(event) => {
          inputState.setQuery(event.target.value)
        }}
      />
      <div className='search-actions'>
        <SearchEnginePicker
          selectedEngine={inputState.searchEngine ?? null}
          searchEngines={inputState.searchEngineOptions}
          onSelectEngine={(engine) => {
            inputState.selectSearchEngine(engine)
            focusInput()
          }}
          onCustomizeClick={props.showSearchSettings}
        />
        <div className='toggle'>{props.renderInputToggle?.()}</div>
        <Button
          fab
          kind='filled'
          className='search-button'
          isDisabled={!inputState.query}
          onClick={inputState.openSearch}
        >
          <Icon name='arrow-up' />
        </Button>
      </div>
      <div className='results-container'>
        <SearchResults
          options={inputState.resultOptions}
          selectedOption={inputState.selectedResultOption}
          onOptionClick={inputState.openResultOption}
          onSearchSuggestionsEnabled={focusInput}
        />
      </div>
    </div>
  )
}
