/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import Icon from '@catsxp/leo/react/icon'
import Button from '@catsxp/leo/react/button'

import { getPlaylistAPI } from '../api/api'
import { getLocalizedString } from '../utils/l10n'

export function AddMediaFromPageButton () {
  return (
    <Button
      kind='outline'
      onClick={() => {
        getPlaylistAPI().showAddMediaToPlaylistUI()
      }}
    >
      <div slot='icon-before'>
        <Icon name='product-playlist-add' />
      </div>
      <div>{getLocalizedString('catsxpPlaylistAddMediaFromPage')}</div>
    </Button>
  )
}
