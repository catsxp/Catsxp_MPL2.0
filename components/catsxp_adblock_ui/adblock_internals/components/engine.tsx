/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { RegexDebugEntry, Regex } from './regex'

export class EngineDebugInfo {
  compiled_regex_count: number = 0
  regex_data: RegexDebugEntry[] = []
  flatbuffer_size: number = 0
}

interface Props {
  caption: string
  info: EngineDebugInfo
}

export const EngineRegexList = (props: Props) => {
  const items = props.info.regex_data.map((d, index) => (
    <Regex
      key={index}
      regex={d}
    />
  ))

  return (
    <div>
      <table>
        <caption>
          <h2>{props.caption} Regexes</h2>
        </caption>
        <tbody>
          <tr>
            <th>ID</th>
            <th>Usage count</th>
            <th>Unused (sec)</th>
            <th>Regex</th>
            <th>Actions</th>
          </tr>
          {items}
        </tbody>
      </table>
    </div>
  )
}
