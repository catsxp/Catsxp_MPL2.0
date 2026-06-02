/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import styled, { css } from 'styled-components'

import { StyledCustomBackgroundOptionImage } from '../../../components/default'

interface Props {
  images: NewTab.ImageBackground[]
}

const RectangularBackgroundImage = styled(StyledCustomBackgroundOptionImage)`
  border-radius: 0;
`

const StyledGrid = styled.div<Props>`
  display: grid;
  ${p => p.images.length === 4
    ? css`
      grid-template-rows: repeat(2, auto);
      grid-template-columns: repeat(2, auto);`
    : css`
      grid-template-rows: repeat(1, auto);
      grid-template-columns: repeat(${p.images.length}, auto);`
  }
  width: 100%;
  height: 100%;

  ${p => p.images.length === 4
    ? css`
      & > :nth-child(1) { border-radius: 10px 0 0 0 }
      & > :nth-child(2) { border-radius: 0 10px 0 0 }
      & > :nth-child(3) { border-radius: 0 0 0 10px }
      & > :nth-child(4) { border-radius: 0 0 10px 0 }`
    : css`
      & > :first-child { border-radius: 10px 0 0 10px }
      & > :last-child { border-radius: 0 10px 10px 0 }`
  }
  & > :only-child { border-radius: 10px }
`

export default function BackgroundImageTiles ({ images }: Props) {
  images = images.slice(0, 4)
  return (
    <StyledGrid images={images}>
        {images.map(image => <RectangularBackgroundImage key={image.wallpaperImageUrl} selected={false} image={image.wallpaperImageUrl}/>)}
    </StyledGrid>)
}
