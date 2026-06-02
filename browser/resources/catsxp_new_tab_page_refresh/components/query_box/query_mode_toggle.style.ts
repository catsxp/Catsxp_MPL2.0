/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { color, font } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  .item {
    --leo-icon-size: 18px;
    --leo-icon-color: ${color.neutral[30]};
    --leo-segmented-control-item-padding: 4px;
    --leo-segmented-control-item-icon-gap: 4px;
    --leo-segmented-control-item-font: ${font.small.regular};
    --leo-segmented-control-item-color: ${color.neutral[30]};
  }

  .selected {
    --leo-segmented-control-item-padding: 6px;
    --leo-icon-color: ${color.neutral[50]};
    --leo-segmented-control-item-color: ${color.neutral[50]};
  }

  .icon {
    // fix issue with icons not rendering until clicked
    display: inline;
  }
`
