/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { color } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  & {
    background: ${color.page.background};
    padding: 16px 16px 16px 12px;
    display: flex;
    flex-direction: column;
    gap: 16px;
    border-bottom: solid 1px ${color.divider.subtle};
  }

  .header {
    display: flex;
    gap: 4px;
    align-items: flex-start;

    leo-button {
      --leo-button-padding: 4px;

      border-radius: 50%;
      flex: 0;

      &:hover {
        background: ${color.button.hover};
      }
    }
  }

  .text {
    flex: 1 1 auto;
    overflow: hidden;
  }

  .host {
    color: ${color.text.secondary};
  }
`
