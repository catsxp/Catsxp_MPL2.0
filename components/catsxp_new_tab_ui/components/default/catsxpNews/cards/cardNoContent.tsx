/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { getLocale } from '../../../../../common/locale'
import { UnidealMessageCard } from './cardError'

interface Props {
  onCustomize: () => unknown
}

export default function CardNoContent (props: Props) {
  return (
    <UnidealMessageCard
      heading={getLocale(S.CATSXP_NEWS_NO_CONTENT_HEADING)}
      message={getLocale(S.CATSXP_NEWS_NO_CONTENT_MESSAGE)}
      actionLabel={getLocale(S.CATSXP_NEWS_NO_CONTENT_ACTION_LABEL)}
      onActionClick={props.onCustomize}
    />
  )
}
