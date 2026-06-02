/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { TopSite } from '../../state/top_sites_store'
import { faviconURL } from '../../lib/favicon_url'

function sanitizeTileURL(url: string) {
  try {
    return new URL(url).toString()
  } catch {
    return ''
  }
}

interface Props {
  topSite: TopSite
  canDrag: boolean
  onContextMenu?: (event: React.MouseEvent) => void
  onNavigate: () => void
}

export function TopSitesTile(props: Props) {
  const { favicon, title, url } = props.topSite

  function onContextMenu(event: React.MouseEvent) {
    if (props.onContextMenu) {
      event.preventDefault()
      props.onContextMenu(event)
    }
  }

  return (
    <a
      className='top-site-tile'
      href={sanitizeTileURL(url)}
      draggable={props.canDrag}
      onClick={props.onNavigate}
      onDragStart={(event) => {
        event.dataTransfer.setData('text/uri-list', url)
      }}
    >
      <span
        className='top-site-icon'
        onContextMenu={onContextMenu}
      >
        <img src={favicon || faviconURL(url)} />
      </span>
      <span className='top-site-title'>{title}</span>
    </a>
  )
}
