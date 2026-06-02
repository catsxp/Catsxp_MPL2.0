/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { color, font } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  .actions {
    padding: 16px;
    display: flex;
    flex-wrap: wrap;
    align-items: center;
    gap: 8px;
    border-top: solid 1px ${color.divider.subtle};

    > * {
      flex: 1 1 calc(50% - 8px);
      white-space: nowrap;
    }
  }

  .try-off {
    padding: 12px 8px 16px;
    border-top: solid 1px ${color.divider.subtle};
    background: ${color.page.background};
    color: ${color.text.tertiary};
    font: ${font.small.regular};
    text-align: center;

    a {
      color: inherit;
    }
  }

  &:nth-child(2) .actions {
    border: none;
    padding-top: 8px;
  }
`
