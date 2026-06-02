/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import {
  StyledStatsItemContainer,
  StyledStatsItem,
  StyledStatsItemCounter,
  StyledStatsItemText,
  StyledStatsItemDescription
} from './style'

export interface StatsProps {
  testId?: string
  children?: React.ReactNode
}

/**
 * Styled container block around stat items used in new tab page
 * @prop {string} testId - the component's id used for testing purposes
 * @prop {React.ReactNode} children - the child elements
 */
export function StatsContainer ({ testId, children }: StatsProps) {
    return <StyledStatsItemContainer data-testid={testId}>{children}</StyledStatsItemContainer>
}

export interface StatsItemProps {
  testId?: string
  counter: string | number
  text?: string
  description: string
}

/**
 * Individual stat block used in new tab page
 * @prop {string} testId - the component's id used for testing purposes
 * @prop {string | number} counter - the stat counter
 * @prop {string} text - descriptive text that goes along the stat
 * @prop {string} description - describes what the counter is showing
 */
export function StatsItem ({ testId, counter, text, description }: StatsItemProps) {
    return <StyledStatsItem data-testid={testId}>
        <StyledStatsItemCounter>{counter}</StyledStatsItemCounter>
          {text && <StyledStatsItemText>{text}</StyledStatsItemText>}
        <StyledStatsItemDescription>{description}</StyledStatsItemDescription>
      </StyledStatsItem>
}
