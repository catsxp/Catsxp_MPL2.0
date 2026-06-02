/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { color, font } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  a {
    text-decoration: none;
    color: inherit;
  }

  .photo-credits {
    color: ${color.white};
    font: ${font.xSmall.regular};
    text-shadow: 0 1px 0 rgba(255, 255, 255, 0.10);
    white-space: nowrap;
    opacity: .5;
  }

  .sponsored-logo {
    --leo-icon-size: 20px;

    width: min-content;
    display: flex;
    flex-direction: column;
    align-items: end;
    color: ${color.white};

    leo-icon {
      opacity: 0;
      transition: opacity 200ms;
    }

    img {
      margin-top: 2px;
      width: 170px;
      height: auto;
    }

    &:hover {
      leo-icon {
        opacity: .7;
      }
    }
  }
`
