/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { color, font } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

import talkGraphic from '../../assets/talk_graphic.svg'

export const style = scoped.css`
  & {
    flex-grow: 1;
    display: flex;
    flex-direction: column;
    gap: 8px;
  }

  .title {
    font: ${font.components.buttonSmall};
  }

  .content {
    flex-grow: 1;
    display: flex;
    align-items: center;
  }

  .graphic {
    background-image: url(${talkGraphic});
    background-repeat: no-repeat;
    background-size: contain;
    background-position: center center;
    width: 56px;
    align-self: stretch;
  }

  .text {
    flex: 1 1 auto;
    display: flex;
    flex-direction: column;
    gap: 4px;
    font: ${font.small.regular};
    color: ${color.text.tertiary};
    padding: 0 8px;
  }

  .header {
    font: ${font.default.semibold};
    color: ${color.text.primary};
  }

  .actions {
    padding: 0 8px;
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 4px;

    leo-button {
      --leo-button-color: rgba(255, 255, 255, 0.20);
      white-space: nowrap;
    }

    a {
      opacity: 0.5;
      color: #fff;
      font: ${font.xSmall.regular};
      text-underline-position: under;
    }
  }
`
