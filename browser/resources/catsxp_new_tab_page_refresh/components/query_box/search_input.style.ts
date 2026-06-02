/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { color, font } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`

  & {
    display: flex;
    flex-direction: column;
  }

  input {
    margin: 12px 16px 8px;
    border: none;
    padding: 0;
    font: ${font.large.regular};
    outline: none;
    background: inherit;
  }

  .search-actions {
    --search-engine-icon-size: 20px;

    display: flex;
    align-items: center;
    gap: 8px;
    padding: 0 8px 8px;
  }

  .toggle {
    margin-inline: auto 0;
  }

  .search-button {
    --leo-button-padding: 8px;
    --leo-button-radius: 50%;

    flex: 0 0 auto;
  }

  .results-container {
    display: none;
  }

  &:focus-within .results-container {
    display: unset;
  }

  .results-container:not(:empty) {
    border-top: solid 1px ${color.divider.subtle};
  }

  &.single-line {
    flex-direction: row;
    gap: 8px;

    .search-actions {
      order: -1;
    }
  }

`
