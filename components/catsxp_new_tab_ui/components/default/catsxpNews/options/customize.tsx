/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import styled from 'styled-components'
import { getLocale } from '../../../../../common/locale'
import { Button } from '../default'

type StyleProps = {
  show: boolean
}

type Props = StyleProps & {
  onCustomizeCatsxpNews: () => any
}

const Hideable = styled('div')<StyleProps>`
  pointer-events: ${p => p.show ? 'auto' : 'none'};
  position: fixed;
  right: 20px;
  bottom: 20px;
  opacity: ${p => p.show ? 1 : 0};
  transition: opacity 1s ease-in-out;
`

export default function Customize (props: Props) {
  return (
    <Hideable show={props.show}>
      <Button
        aria-hidden={!props.show}
        disabled={!props.show}
        onClick={props.onCustomizeCatsxpNews}
      >
        {getLocale('customize')}
      </Button>
    </Hideable>
  )
}
