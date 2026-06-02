/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { color } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  & {
    flex: 1 1 auto;
    display: flex;
    align-items: stretch;
    pointer-events: auto;
  }

  a {
    --leo-icon-size: 20px;

    flex: 1 1 auto;
    display: flex;
    flex-direction: column;
    align-items: end;
    color: ${color.white};

    leo-icon {
      opacity: 0;
      transition: opacity 200ms;
    }

    &:hover {
      leo-icon {
        opacity: .7;
      }
    }
  }
`
