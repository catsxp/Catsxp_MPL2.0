/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import Alert from '@catsxp/leo/react/alert'
import styled from 'styled-components'

export const Container = styled.div`
  padding: 0 var(--leo-spacing-xl) var(--leo-spacing-xl);
`

export const HeaderRow = styled.div`
  margin: 0 var(--leo-spacing-xl) var(--leo-spacing-xl);
  display: flex;
  align-items: center;
  gap: var(--leo-spacing-m);
`

export const HeaderTextColumn = styled.div`
  display: flex;
  flex-direction: column;
`

export const HeaderTitle = styled.div`
  font: var(--leo-font-default-regular);
  color: var(--leo-color-text-primary);
  margin-bottom: var(--leo-spacing-xs);
`

export const HeaderDescription = styled.div`
  font: var(--leo-font-small-regular);
  color: var(--leo-color-text-tertiary);
`

export const StyledAlert = styled(Alert)`
  padding: var(--leo-spacing-m) var(--leo-spacing-xl) var(--leo-spacing-xl);
`

