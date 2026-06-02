/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { Meta, StoryObj } from '@storybook/react'

import { App } from '../components/app'

interface StorybookAppProps {}

function StorybookApp(props: StorybookAppProps) {
  return (
    <div style={{ position: 'absolute', inset: 0 }}>
      <App />
    </div>
  )
}

export default {
  title: 'Welcome Page/App',
  component: StorybookApp,
} satisfies Meta<typeof StorybookApp>

export const NewTabPage: StoryObj<typeof StorybookApp> = {}
