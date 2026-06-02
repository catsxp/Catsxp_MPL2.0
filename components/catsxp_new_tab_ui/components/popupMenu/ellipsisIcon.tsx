/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import styled from 'styled-components'

interface Props {
  className?: string
}

const IconSVG = styled('svg')`
  fill: currentColor;
  width: 100%;
  height: 100%;
`

export default function EllipsisIcon (props: Props) {
  return (
    <IconSVG className={props.className} xmlns={'http://www.w3.org/2000/svg'} viewBox="0 0 24 24">
      <path d={'M18 14.25a2.25 2.25 0 110-4.5 2.25 2.25 0 010 4.5zm-6 0a2.25 2.25 0 110-4.5 2.25 2.25 0 010 4.5zm-6 0a2.25 2.25 0 110-4.5 2.25 2.25 0 010 4.5z'} fillRule={'evenodd'}/>
    </IconSVG>
  )
}
