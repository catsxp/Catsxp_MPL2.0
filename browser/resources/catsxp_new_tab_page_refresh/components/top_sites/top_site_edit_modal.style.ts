/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { font } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  & {
    width: 500px;
    max-width: 100%;
    padding: 24px;
    display: flex;
    flex-direction: column;
    gap: 16px;
  }

  .label {
    font: ${font.small.semibold};
  }

  .actions {
    padding-top: 8px;
    display: flex;
    justify-content: flex-end;
    align-items: center;
    gap: 8px;

    leo-button {
      flex: 0 0 auto;
    }
  }
`
