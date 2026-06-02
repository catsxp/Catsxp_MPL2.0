/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { color, font } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  .engine-icon {
    --leo-icon-size: var(--search-engine-icon-size, 16px);
    height: var(--leo-icon-size);
    width: var(--leo-icon-size);
    display: block;
  }

  .engine-picker-button {
    padding: 7px;
    border-radius: 4px;

    &:hover {
      background-color: ${color.container.highlight};
    }

    leo-button {
      display: block;
    }
  }

  leo-menu-item {
    --leo-icon-size: 20px;

    display: flex;
    align-items: center;
    gap: 16px;
    min-width: 180px;

    &[data-customize] {
      font: ${font.components.buttonSmall};
      color: ${color.text.secondary};
      justify-content: center;
    }
  }

  .divider {
    border-top: solid 1px ${color.divider.subtle};
  }
`
