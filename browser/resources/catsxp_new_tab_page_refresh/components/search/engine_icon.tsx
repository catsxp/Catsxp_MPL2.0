/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Icon from '@catsxp/leo/react/icon'

import { SearchEngineInfo } from '../../state/search_store'
import { SafeImage } from '../common/safe_image'

interface Props {
  engine: SearchEngineInfo
}

export function EngineIcon(props: Props) {
  const { engine } = props
  const iconName = getNamedIcon(engine.host)
  if (iconName) {
    return (
      <Icon
        name={iconName}
        className='engine-icon'
      />
    )
  }
  return (
    <SafeImage
      src={engine.faviconUrl}
      className='engine-icon'
    />
  )
}

function getNamedIcon(engineHost: string) {
  switch (engineHost) {
    case 'www.google.com':
      return 'google-color'
    case 'duckduckgo.com':
      return 'duckduckgo-color'
    case 'search.catsxp.com':
      return 'social-catsxp-release-favicon-fullheight-color'
    case 'www.bing.com':
      return 'bing-color'
    case 'www.qwant.com':
      return 'qwant-color'
    case 'www.startpage.com':
      return 'startpage-color'
    case 'search.yahoo.com':
      return 'yahoo-color'
    case 'yandex.com':
      return 'yandex-color'
    case 'www.ecosia.org':
      return 'ecosia-color'
  }
  return ''
}
