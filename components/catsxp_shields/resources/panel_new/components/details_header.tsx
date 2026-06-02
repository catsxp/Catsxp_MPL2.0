/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import Button from '@catsxp/leo/react/button'
import Icon from '@catsxp/leo/react/icon'

import { useShieldsApi } from '../api/shields_api_context'
import { getString } from './strings'

import { style } from './details_header.style'

interface Props {
  title: string
  onBack: () => void
  children?: React.ReactNode
}

export function DetailsHeader(props: Props) {
  const api = useShieldsApi()
  const { data: siteBlockInfo } = api.useGetSiteBlockInfo()
  const host = siteBlockInfo?.host ?? ''

  return (
    <div data-css-scope={style.scope}>
      <div className='header'>
        <Button
          onClick={props.onBack}
          kind='plain-faint'
          fab
          size='medium'
          aria-label={getString('CATSXP_SHIELDS_GO_BACK')}
        >
          <Icon name='arrow-left' />
        </Button>
        <div className='text'>
          <h4>{props.title}</h4>
          <div className='host overflow-ellipsis-start'>
            {'\u2068'}
            {host}
            {'\u2069'}
          </div>
          {props.children}
        </div>
      </div>
    </div>
  )
}
