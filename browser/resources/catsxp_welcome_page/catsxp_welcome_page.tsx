/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { createRoot } from 'react-dom/client'
import { setIconBasePath } from '@catsxp/leo/react/icon'

import { App } from './components/app'

setIconBasePath('chrome://resources/catsxp-icons')

createRoot(document.getElementById('root')!).render(<App />)
