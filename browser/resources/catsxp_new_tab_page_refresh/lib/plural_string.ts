/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { PluralStringProxyImpl } from 'chrome://resources/js/plural_string_proxy.js'

export function usePluralString(key: string, count: number) {
  const [pluralString, setPluralString] = React.useState('')
  React.useEffect(() => {
    PluralStringProxyImpl.getInstance()
      .getPluralString(key, count)
      .then(setPluralString)
  }, [key, count])
  return pluralString
}
