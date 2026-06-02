/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import styled from 'styled-components'
import { CaratStrongDownIcon } from 'catsxp-ui/components/icons'
import { getLocale } from '../../../../common/locale'

const Hint = styled('div')<{}>`
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 12px;
  text-align: center;
  font-size: 15px;
  color: var(--override-readability-color, #FFFFFF);
  > p {
    margin: 0;
  }
`

const Graphic = styled('div')`
  width: 16px;
  height: 16px;
`

export default function CatsxpNewsHint () {
  return (
    <Hint>
      <p>{getLocale('catsxpNewsScrollHint')}</p>
      <Graphic>
        <CaratStrongDownIcon />
      </Graphic>
    </Hint>
  )
}
