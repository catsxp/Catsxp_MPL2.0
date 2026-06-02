/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Icon from '@catsxp/leo/react/icon'
import { getLocale } from '../../../common/locale'
import { AddSiteTile, TileImageContainer, TileTitle } from '../../components/default'

interface Props {
  showEditTopSite: () => void
  isDragging: boolean
}

export default function AddSite ({ showEditTopSite, isDragging }: Props) {
  return <AddSiteTile onClick={showEditTopSite} isDragging={isDragging}>
      <TileImageContainer>
        <Icon name='plus-add' />
      </TileImageContainer>
      <TileTitle>
        {getLocale('addTopSiteDialogTitle')}
      </TileTitle>
    </AddSiteTile>
}
