/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

interface Props {
  showSearchSettings: () => void
}

const QueryBox = React.lazy(() => import('./query_box'))

export function LazyQueryBox(props: Props) {
  return (
    <React.Suspense>
      <QueryBox showSearchSettings={props.showSearchSettings} />
    </React.Suspense>
  )
}
