/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { color } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  & {
    --leo-menu-max-height: max-content;

    position: absolute;
    inset-block-start: 12px;
    inset-inline-end: 12px;
  }

  leo-button {
    --leo-icon-size: 16px;
    --leo-icon-color: ${color.icon.default};

    padding: 4px;
    opacity: 0;
    transition: opacity 120ms;

    .ntp-widget:hover & {
      opacity: 1;
    }
  }

  leo-menu-item {
    --leo-icon-size: 24px;

    display: flex;
    align-items: center;
    gap: 12px;
  }
`
