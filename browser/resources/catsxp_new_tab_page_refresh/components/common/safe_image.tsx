/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { placeholderImageSrc } from '../../lib/image_loader'

interface Props {
  src: string
  className?: string
  targetSize?: { width: number; height: number }
}

export function SafeImage(props: Props) {
  let { src } = props
  if (src) {
    src = 'chrome://catsxp-image?url=' + encodeURIComponent(src)
    if (props.targetSize) {
      let { width, height } = props.targetSize
      width = Math.round(width * window.devicePixelRatio)
      height = Math.round(height * window.devicePixelRatio)
      src += `&target_size=${width}x${height}`
    }
  }

  return (
    <img
      src={src || placeholderImageSrc}
      loading='lazy'
      className={props.className}
      onError={(event) => {
        event.currentTarget.src = placeholderImageSrc
      }}
      onLoad={(event) => {
        event.currentTarget?.classList.add('loaded')
      }}
    />
  )
}
