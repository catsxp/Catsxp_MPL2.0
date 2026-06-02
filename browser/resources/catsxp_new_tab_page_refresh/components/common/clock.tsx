/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { ClockFormat } from '../../state/new_tab_store'
import { useNewTabState } from '../../context/new_tab_context'

export function Clock() {
  const showClock = useNewTabState((s) => s.showClock)
  const clockFormat = useNewTabState((s) => s.clockFormat)
  const [time, setTime] = React.useState(Date.now())

  const formatter = React.useMemo(() => {
    return new Intl.DateTimeFormat(undefined, {
      hour: 'numeric',
      minute: 'numeric',
      hourCycle:
        clockFormat === ClockFormat.k12
          ? 'h12'
          : // For 24-hour mode, use h23, which starts at 0:00 instead of 24:00.
            clockFormat === ClockFormat.k24
            ? 'h23'
            : undefined,
    })
  }, [clockFormat])

  React.useEffect(() => {
    if (!showClock) {
      return
    }
    const timer = setInterval(() => setTime(Date.now()), 2000)
    return () => clearInterval(timer)
  }, [showClock])

  if (!showClock) {
    return null
  }

  return (
    <>
      {formatter.formatToParts(time).map((item) => {
        if (item.type === 'dayPeriod') {
          return (
            <span
              className='day-period'
              key='day-period'
            >
              {item.value}
            </span>
          )
        }
        return item.value
      })}
    </>
  )
}
