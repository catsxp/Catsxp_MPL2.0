/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { color, effect } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  :scope {
    --self-fade-duration: 120ms;

    position: fixed;
    margin: auto;
    border-radius: 16px;
    background: ${color.container.background};
    box-shadow: ${effect.elevation['05']};
    display: none;
    opacity: 0;
    transform: scale(1);

    transition:
      opacity var(--self-fade-duration),
      transform var(--self-fade-duration),
      display var(--self-fade-duration) allow-discrete,
      overlay var(--self-fade-duration) allow-discrete;

    &:modal {
      display: block;
      opacity: 1;

      @starting-style {
        opacity: 0;
        transform: scale(.9);
      }
    }

    &::backdrop {
      background: rgba(0, 0, 0, 0);
      transition: all var(--self-fade-duration) allow-discrete;
    }

    &:modal::backdrop {
      background: rgba(0, 0, 0, 0.15);

      @starting-style {
        background: rgba(0, 0, 0, 0);
      }
    }
  }

  .close {
    position: absolute;
    inset-block: 16px auto;
    inset-inline: auto 16px;
  }
`
