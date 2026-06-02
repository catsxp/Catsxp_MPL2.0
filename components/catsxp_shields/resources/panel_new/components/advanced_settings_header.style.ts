/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { color } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`

  .view-toggle {
    --leo-icon-size: 20px;

    padding: 8px 16px;
    display: flex;
    align-items: center;
    gap: 16px;
    cursor: pointer;
    width: 100%;

    span {
      flex: 1 1 auto;
    }

    &:hover, [data-expanded=true] & {
      --leo-icon-color: ${color.icon.interactive};
      color: ${color.text.interactive};
    }
  }

`
