/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { style } from './ntp_widget.style'

interface Props {
  children: React.ReactNode
}

export function NtpWidget(props: Props) {
  return (
    <div
      data-css-scope={style.scope}
      className='ntp-widget'
      data-theme='dark'
    >
      {props.children}
    </div>
  )
}
