/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import styled from 'styled-components'
import { LoaderIcon } from 'catsxp-ui/components/icons'

const Loading = styled('div')`
  width: 100%;
  height: 100%;
  display: flex;
  align-items: center;
  justify-content: center;
`

const Graphic = styled('div')`
  color: var(--loading-color, ${p => p.theme.color.subtleActive});
  width: 50px;
  height: 50px;
  align-self: center;
`

export default function LoadingComponent () {
  return (
    <Loading aria-busy='true'>
      <Graphic aria-label='Loading'>
        <LoaderIcon />
      </Graphic>
    </Loading>
  )
}
