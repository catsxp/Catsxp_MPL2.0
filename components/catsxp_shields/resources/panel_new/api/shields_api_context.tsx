/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { ShieldsApi } from './shields_api'

const ShieldsApiContext = React.createContext<ShieldsApi | null>(null)

export function useShieldsApi(): ShieldsApi {
  const api = React.useContext(ShieldsApiContext)
  if (!api) {
    throw new Error('useShieldsApi must be used within ShieldsApiProvider')
  }
  return api
}

interface ProviderProps {
  children: React.ReactNode
  api: ShieldsApi
}

export function ShieldsApiProvider({ children, api }: ProviderProps) {
  React.useEffect(() => () => api.close(), [api])
  return (
    <ShieldsApiContext.Provider value={api}>
      {children}
    </ShieldsApiContext.Provider>
  )
}
