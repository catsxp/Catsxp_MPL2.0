/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Button from '@catsxp/leo/react/button'
import ButtonMenu from '@catsxp/leo/react/buttonMenu'

import { getString } from '../../lib/strings'
import { SearchEngineInfo } from '../../state/search_store'
import { EngineIcon } from './engine_icon'

import { style } from './search_engine_picker.style'

interface Props {
  selectedEngine: SearchEngineInfo | null
  searchEngines: SearchEngineInfo[]
  onSelectEngine: (engine: SearchEngineInfo) => void
  onCustomizeClick: () => void
}

export function SearchEnginePicker(props: Props) {
  const { searchEngines, selectedEngine } = props
  return (
    <div data-css-scope={style.scope}>
      <ButtonMenu>
        <div
          className='engine-picker-button'
          slot='anchor-content'
        >
          <Button
            fab
            kind='plain-faint'
          >
            {selectedEngine ? (
              <EngineIcon engine={selectedEngine} />
            ) : (
              <span className='engine-icon' />
            )}
          </Button>
        </div>
        {searchEngines.map((engine) => (
          <leo-menu-item
            key={engine.host}
            onClick={() => props.onSelectEngine(engine)}
          >
            <EngineIcon engine={engine} />
            {engine.name}
          </leo-menu-item>
        ))}
        <div className='divider' />
        <leo-menu-item
          onClick={props.onCustomizeClick}
          data-customize='customize'
        >
          {getString(S.NEW_TAB_SEARCH_CUSTOMIZE_ENGINE_LIST_TEXT)}
        </leo-menu-item>
      </ButtonMenu>
    </div>
  )
}
