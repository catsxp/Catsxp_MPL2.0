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
  width: 50px;
  height: 50px;
  align-self: center;

  svg {
    fill: white;
  }
`

export default function Loader () {
  return (
    <Loading aria-busy='true'>
      <Graphic aria-label='Loading'>
        <LoaderIcon />
      </Graphic>
    </Loading>
  )
}
