/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { color, font } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  & {
    margin: 0 8px;
    padding: 8px 16px 8px 24px;
    display: flex;
    align-items: center;
    gap: 16px;

    p {
      color: ${color.text.tertiary};
      font: ${font.small.regular};
    }
  }
`
