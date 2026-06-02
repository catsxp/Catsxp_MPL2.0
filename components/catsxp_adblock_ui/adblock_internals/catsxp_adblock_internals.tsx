/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { createRoot } from 'react-dom/client'

// Components
import { App } from './components/app'

function initialize() {
  const container = document.getElementById('root')
  if (container) {
    const root = createRoot(container)
    root.render(<App />)
  }
}

document.addEventListener('DOMContentLoaded', initialize)
