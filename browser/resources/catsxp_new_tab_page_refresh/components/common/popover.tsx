/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

interface Props {
  className?: string
  isOpen: boolean
  children: React.ReactNode
  onClose: () => void
}

export function Popover(props: Props) {
  const elementRef = React.useRef<HTMLDivElement>(null)

  React.useLayoutEffect(() => {
    elementRef.current?.setAttribute('popover', 'auto')
  }, [])

  React.useEffect(() => {
    if (props.isOpen) {
      elementRef.current?.showPopover()
    } else {
      elementRef.current?.hidePopover()
    }
  }, [props.isOpen])

  React.useEffect(() => {
    const onToggle = (event: ToggleEvent) => {
      if (event.newState === 'closed') {
        props.onClose()
      }
    }
    const elem = elementRef.current
    elem?.addEventListener('toggle', onToggle)
    return () => elem?.removeEventListener('toggle', onToggle)
  }, [props.onClose])

  return (
    <div
      ref={elementRef}
      className={props.className}
    >
      {props.children}
    </div>
  )
}
