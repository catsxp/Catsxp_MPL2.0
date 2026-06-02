/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import styled from 'styled-components'

import { color, font, gradient } from '@catsxp/leo/tokens/css/variables'

export const Content = styled.div.attrs({ 'data-theme': 'dark' })`
  color: ${color.white};
  font: ${font.small.regular};
`

export const WelcomeText = styled.div``

export const ActionsWrapper = styled.div`
  margin-top: 16px;
  text-align: center;
  display: flex;
  flex-direction: column;
  justify-content: stretch;
  gap: 16px;
`

export const CatsxpTalkIcon = styled.div`
  --leo-icon-size: 24px;
  --leo-icon-color: ${gradient.iconsActive};
`

export const StyledTitle = styled.div`
  margin-bottom: 24px;
  font: ${font.heading.h4};
  color: ${color.white};
  display: flex;
  align-items: center;
  gap: 8px;
`

export const Privacy = styled.div``

export const PrivacyLink = styled.a`
  color: ${color.white};
  text-decoration: none;
`
