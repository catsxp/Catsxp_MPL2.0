/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { color, font } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  & {
    min-height: 100%;
    display: flex;
    flex-direction: column;
    gap: 8px;
  }

  .title {
    font: ${font.components.buttonSmall};
  }

  .data {
    flex: 1 1 auto;
    display: flex;
    align-items: center;
    color: ${color.primitive.neutral[90]};
    font: ${font.xSmall.regular};

    > div {
      flex-grow: 1;
      display: flex;
      align-items: flex-start;
      justify-content: space-between;
      gap: 24px;
    }
  }

  .ads-blocked {
    --self-value-color: ${color.primitive.orange[70]};
  }

  .bandwidth-saved {
    --self-value-color: ${color.primitive.primary[70]};
  }

  .value {
    color: var(--self-value-color, #fff);
    font: ${font.heading.h3};
  }

  .units {
    font: ${font.default.semibold};
    text-transform: capitalize;
  }
`
