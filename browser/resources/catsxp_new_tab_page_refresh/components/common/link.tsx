/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { sanitizeExternalURL } from '../../lib/url_sanitizer'

interface Props {
  url: string
  className?: string
  onClick?: () => void
  onContextMenu?: React.MouseEventHandler<HTMLAnchorElement>
  openInNewTab?: boolean
  children: React.ReactNode
}

export function Link(props: Props) {
  const sanitizedURL = sanitizeExternalURL(props.url)
  if (!sanitizedURL) {
    return <span className={props.className}>{props.children}</span>
  }
  return (
    <a
      href={sanitizedURL}
      className={props.className}
      rel='noopener noreferrer'
      target={props.openInNewTab ? '_blank' : '_self'}
      onClick={props.onClick}
      onContextMenu={props.onContextMenu}
    >
      {props.children}
    </a>
  )
}

export function openLink(url: string) {
  const sanitizedURL = sanitizeExternalURL(url)
  if (sanitizedURL) {
    window.open(sanitizedURL, '_self', 'noopener noreferrer')
  }
}
