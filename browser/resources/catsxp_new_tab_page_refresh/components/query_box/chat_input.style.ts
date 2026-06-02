/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  & {
    container-type: inline-size;
  }

  form {
    border: none !important;
  }

  .chat-tools {
    --leo-dialog-padding: 0;

    position: relative;

    > * {
      position: absolute;
      inset: 2px 0 auto;
    }

    leo-buttonmenu > * {
      max-width: 100cqi;
    }
  }
`
