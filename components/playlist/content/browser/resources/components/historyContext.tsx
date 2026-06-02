/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { useHistory, useLocation } from 'react-router'
import { History } from 'history'

export let history: History | undefined

export function HistoryContext (props: React.PropsWithChildren<{}>) {
  const h = useHistory()
  const location = useLocation()

  React.useEffect(() => {
    history = h
    return () => (history = undefined)
  }, [h])

  // When the component mounts, restore the location from local storage.
  // This happens only when the initial location is the default location.
  React.useEffect(() => {
    const lastLocation = localStorage.getItem('lastLocation')
    if (location.pathname === '/' && lastLocation) {
      history?.replace(lastLocation)
    }
  }, [])

  // Record the current location in local storage
  React.useEffect(() => {
    localStorage.setItem('lastLocation', location.pathname)
  }, [location])

  return <>{props.children}</>
}
