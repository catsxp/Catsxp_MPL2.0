/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { color, font } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  & {
    display: flex;
    flex-direction: column;
  }

  .search-engines {
    padding: 24px;
  }

  .search-engine-list {
    --leo-checkbox-flex-direction: row-reverse;
    --leo-checkbox-label-gap: 16px;
    --leo-icon-size: 20px;

    padding: 24px 0;
    display: flex;
    flex-direction: column;
    gap: 16px;
  }

  .engine-name {
    flex: 1 1 auto;
  }

  .engine-icon {
    width: 20px;
    height: 20px;
  }

  h4 {
    font: ${font.default.semibold};
  }

  .divider {
    height: 1px;
    background: ${color.divider.subtle};
  }

  .customize-link {
    --leo-icon-size: 20px;

    margin-top: 16px;
    display: inline-flex;
    align-items: center;
    gap: 8px;
    text-decoration: none;
    color: ${color.text.primary};
  }
`
