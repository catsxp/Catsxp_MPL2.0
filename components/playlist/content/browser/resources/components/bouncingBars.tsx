/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import styled from 'styled-components'

const StyledBouncingBars = styled.div`
  width: 18px;
  height: 18px;
  display: flex;
  justify-content: space-evenly;
  align-items: flex-end;
  padding: 2px;
  box-sizing: border-box;
`

const Bar = styled.div`
  @keyframes bounce {
    0,
    100% {
      height: 100%;
    }
    50% {
      height: 45%;
    }
  }

  --bouncing-duration: 1.5s;

  border-radius: 2px;
  width: 2px;
  height: 100%;
  background-color: white;
  animation: bounce var(--bouncing-duration) infinite;
  transform-origin: bottom center;
  &:nth-child(1) {
    animation-delay: calc(-1 * var(--bouncing-duration) * 0.5);
  }
  &:nth-child(2) {
    animation-delay: calc(-1 * var(--bouncing-duration));
  }
  &:nth-child(3) {
    animation-delay: calc(-1 * var(--bouncing-duration) * 0.625);
  }
  &:nth-child(4) {
    animation-delay: calc(-1 * var(--bouncing-duration) * 0.25);
  }
`

export function BouncingBars () {
  return (
    <StyledBouncingBars>
      <Bar></Bar>
      <Bar></Bar>
      <Bar></Bar>
      <Bar></Bar>
    </StyledBouncingBars>
  )
}
