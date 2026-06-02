/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { OpenNewIcon } from 'catsxp-ui/components/icons'

import createWidget from '../widget/index'
import * as Styled from './logo-style'

interface Props {
  data: NewTab.BrandedWallpaperLogo
  onClickLogo: () => void
}

function Logo ({ data, onClickLogo }: Props) {
  return (
    <>
      <Styled.Image src={data.image} alt={data.alt} />
      <Styled.Anchor href={data.destinationUrl} title={data.alt} onClick={onClickLogo}>
        <Styled.Indicator><OpenNewIcon /></Styled.Indicator>
      </Styled.Anchor>
    </>
  )
}

export default createWidget(Logo)
