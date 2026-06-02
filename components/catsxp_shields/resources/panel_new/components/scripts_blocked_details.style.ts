/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { color, font } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  .list-header {
    padding: 8px 16px;
    display: flex;
    align-items: center;
    gap: 8px;
    font: ${font.default.semibold};

    button {
      margin-inline-start: auto;
      font: ${font.small.link};
      text-decoration: underline;
      color: ${color.text.primary};
    }
  }

  .allow-header {
    color: ${color.systemfeedback.successText};
    background: ${color.systemfeedback.successBackground};
  }

  .block-header {
    color: ${color.systemfeedback.errorText};
    background: ${color.systemfeedback.errorBackground};
  }

  .resource-list {
    padding: 8px;
  }
`
