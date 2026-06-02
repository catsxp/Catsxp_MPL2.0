/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

interface Props {
  caption: string
  memory: { [key: string]: string }
}

export const MemoryInfo = (props: Props) => {
  const items = Object.keys(props.memory).map((key) => {
    const v = props.memory[key]
    return (
      <div key={key}>
        {key} : {v}
      </div>
    )
  })

  return (
    <div>
      <h2>{props.caption}</h2>
      {items}
    </div>
  )
}
