/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { useShieldsApi } from '../api/shields_api_context'

interface Props {
  url: string
  className?: string
  'aria-label'?: string
  children: React.ReactNode
}

export function OpenTabLink(props: Props) {
  const api = useShieldsApi()
  return (
    <a
      href={sanitize(props.url)}
      className={props.className}
      aria-label={props['aria-label']}
      rel='noopener noreferrer'
      target='_blank'
      onClick={(event) => {
        event.preventDefault()
        api.openTab(sanitize(props.url))
      }}
    >
      {props.children}
    </a>
  )
}

function isAllowed(url: string) {
  try {
    return ['https:', 'chrome:'].includes(new URL(url).protocol)
  } catch {
    return false
  }
}

function sanitize(url: string) {
  return isAllowed(url) ? url : ''
}
