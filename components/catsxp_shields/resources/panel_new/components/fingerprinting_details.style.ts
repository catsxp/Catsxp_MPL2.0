/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { font } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  .toggle-list {
    max-width: 380px;
    width: 100%;
    margin-left: auto;
    margin-right: auto;
    padding: 24px;
    display: flex;
    flex-direction: column;
    gap: 12px;

    > * {
      display: flex;
      align-items: center;
      gap: 8px;
      text-transform: capitalize;

      leo-toggle {
        margin-inline-start: auto;
      }
    }
  }
`

style.passthrough.css`
  p.header-text {
    margin-top: 16px;
    font: ${font.small.regular};

    button {
      text-decoration: underline;
    }
  }
`
