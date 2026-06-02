/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { Meta, StoryObj } from '@storybook/react'

import { createMockShieldsAPI } from '../api/shields_api_mock'
import { ShieldsApiProvider } from '../api/shields_api_context'
import { App } from '../components/app'

function StorybookApp() {
  return (
    <div style={{ position: 'absolute', inset: 0 }}>
      <ShieldsApiProvider api={createMockShieldsAPI()}>
        <App />
      </ShieldsApiProvider>
    </div>
  )
}

export default {
  title: 'Shields Panel/Shields',
  component: StorybookApp,
} satisfies Meta<typeof StorybookApp>

export const ShieldsPanel: StoryObj<typeof StorybookApp> = {}
