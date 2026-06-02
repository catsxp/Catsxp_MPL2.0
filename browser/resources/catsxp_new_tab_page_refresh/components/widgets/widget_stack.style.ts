/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { color } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  & {
    flex-grow: 1;
    display: flex;
    align-items: stretch;
  }

  .stack-tabs {
    --leo-icon-size: 16px;
    --leo-icon-color: ${color.icon.default};

    display: flex;
    flex-direction: column;
    border-radius: 16px 0 0 16px;
    overflow: clip;

    > * {
      background: rgba(255, 255, 255, 0.10);
      flex: 1 1 auto;
      padding: 0 16px;
      display: flex;
      align-items: center;
    }

    .active {
      --leo-icon-color: #fff;
      background: inherit;
    }
  }

  .widget {
    flex: 1 1 auto;
    padding: 16px;
    display: flex;
    flex-direction: column;
  }
`
