/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import styled from 'styled-components'

export const MainBox = styled.div`
  background: transparent;
  border-radius: 30px;
  max-width: 800px;
  color: white;
  font-family: ${(p) => p.theme.fontFamily.heading};
  display: flex;
  align-items: center;
  justify-content: center;
  flex-direction: column;

  .view-title {
    font-weight: 400;
    font-size: 40px;
  }

  .icon-box {
    width: 300px;
  }
`
