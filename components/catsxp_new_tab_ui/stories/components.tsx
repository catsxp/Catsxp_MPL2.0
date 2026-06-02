/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { withKnobs } from '@storybook/addon-knobs'
import ThemeProvider from '../../common/CatsxpCoreThemeProvider'
// Components
import LoadingComponent from '../components/loading'
import OutlineButtonComponent from '../components/outlineButton'

export default {
  title: 'New Tab',
  decorators: [
    (Story: any) => <ThemeProvider><Story /></ThemeProvider>,
    withKnobs
  ]
}

export const Loading = () => (
  <div
    style={{ width: '500px', height: '500px', display: 'flex', alignItems: 'center', justifyContent: 'center' }}
  >
    <LoadingComponent />
  </div>
)

export const OutlineButton = () => (
  <div
    style={{ width: '500px', height: '500px', display: 'flex', alignItems: 'center', justifyContent: 'center' }}
  >
    <OutlineButtonComponent>
      Button
    </OutlineButtonComponent>
  </div>
)
