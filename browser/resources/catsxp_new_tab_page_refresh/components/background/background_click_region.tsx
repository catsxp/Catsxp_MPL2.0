/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Icon from '@catsxp/leo/react/icon'

import { Link } from '../common/link'
import {
  useCurrentBackground,
  useBackgroundActions,
} from '../../context/background_context'

import { style } from './background_click_region.style'

export function BackgroundClickRegion() {
  const actions = useBackgroundActions()
  const currentBackground = useCurrentBackground()
  if (currentBackground?.type !== 'sponsored-image') {
    return null
  }

  const url = currentBackground.logo?.destinationUrl
  if (!url) {
    return null
  }

  return (
    <div data-css-scope={style.scope}>
      <Link
        url={url}
        onClick={actions.notifySponsoredImageLogoClicked}
        onContextMenu={(e) => e.preventDefault()}
      >
        <Icon name='launch' />
      </Link>
    </div>
  )
}
