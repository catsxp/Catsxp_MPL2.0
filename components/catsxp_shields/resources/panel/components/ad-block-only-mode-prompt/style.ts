/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import Alert from '@catsxp/leo/react/alert'
import styled from 'styled-components'

export const Container = styled.div`
  padding: var(--leo-spacing-xl);
`

export const Title = styled.div`
  font: var(--leo-font-heading-h4);
`

export const Description = styled.div`
  font: var(--leo-font-default-regular);
  a {
    color: var(--leo-color-text-secondary);
  }
`

export const Actions = styled.div`
  padding-top: var(--leo-spacing-xl);
  display: flex;
  gap: var(--leo-spacing-m);
`

export const StyledAlert = styled(Alert)`
  padding: 0 var(--leo-spacing-xl) var(--leo-spacing-xl);
`

export const ActionsSlotWrapper = styled.div`
  display: flex;
  gap: var(--leo-spacing-m);
`
