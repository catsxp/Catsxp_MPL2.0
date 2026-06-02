/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { color } from '@catsxp/leo/tokens/css/variables'
import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  & {
    position: relative;
    color: ${color.text.primary};
    border-radius: 16px;
    background: ${color.material.thin};
    backdrop-filter: blur(50px);
    display: flex;
    align-items: stretch;

    animation: linear widget-scroll-fade both;
    animation-timeline: --ntp-main-view-timeline;
    animation-range: exit-crossing 10% exit-crossing 100%;
  }

  @keyframes widget-scroll-fade {
    from { opacity: 1; }
    to { opacity: 0; }
  }
`
