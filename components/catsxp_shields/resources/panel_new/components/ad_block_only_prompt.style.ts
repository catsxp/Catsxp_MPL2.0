/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { color } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  & {
    margin: 0 8px;
    border-radius: 8px;
    padding: 16px 24px;
    background: ${color.systemfeedback.infoBackground};
    color: ${color.systemfeedback.infoText};
  }

  .actions {
    margin-top: 16px;
    display: flex;
    align-items: center;
    gap: 8px;
  }
`
