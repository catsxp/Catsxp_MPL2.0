/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import styled from 'styled-components'

export const StyledClock = styled('div')<{}>`
  color: var(--override-readability-color, #FFFFFF);
  box-sizing: border-box;
  line-height: 1;
  user-select: none;
  display: flex;
  -webkit-font-smoothing: antialiased;
  font-family: ${p => p.theme.fontFamily.heading};
`

export const StyledTime = styled('span')<{}>`
  box-sizing: border-box;
  font-size: 78px;
  font-weight: 300;
  color: inherit;
  display: inline-flex;
`

export const StyledTimeSeparator = styled('span')<{}>`
  box-sizing: border-box;
  color: inherit;
  font-size: inherit;
  font-weight: 200;
  /* center colon vertically in the text-content line */
  margin-top: -0.1em;
`
