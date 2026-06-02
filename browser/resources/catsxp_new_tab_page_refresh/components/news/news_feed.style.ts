/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { scoped } from '$web-common/scoped_css'

export const style = scoped.css`
  & {
    min-height: 100vh;
    display: flex;
    flex-direction: column;
    align-items: center;
    margin: 0 30px 30px;
  }
`

style.passthrough.css`
  @keyframes news-control-fade {
    from {
      opacity: 0;
      visibility: hidden;
    }
    80% {
      opacity: 0;
      visibility: visible;
    }
    to {
      opacity: 1;
      visibility: visible;
    }
  }

  .catsxp-news-feed-controls, .catsxp-news-load-new-content-button {
    animation: linear news-control-fade both;
    animation-timeline: scroll();
    animation-range: 0px 100vh;
  }
`
