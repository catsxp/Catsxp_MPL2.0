/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import styled from 'styled-components'

import LeoProgressBar from '@catsxp/leo/react/progressBar'
import { color } from '@catsxp/leo/tokens/css/variables'

export const ProgressBar = styled(LeoProgressBar)`
  position: absolute;
  bottom: 0;
  width: 100%;
  height: 3px;
  --leo-progressbar-radius: 0;
  --leo-progressbar-background-color: color-mix(
    in srgb,
    ${color.white} 40%,
    transparent
  );
`
