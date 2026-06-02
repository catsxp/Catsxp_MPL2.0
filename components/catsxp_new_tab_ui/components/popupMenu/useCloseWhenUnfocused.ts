/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

export default function useCloseWhenUnfocused (ref: React.RefObject<HTMLUListElement>, onClose: () => unknown) {
  // Call onClose when
  // - click outside
  // - lose focus
  // - press esc
  React.useEffect(() => {
    if (!ref.current) {
      return
    }
    const handleFocusChange = (ev: FocusEvent) => {
      if (!ref.current) {
        return
      }
      const isFocusWithinMenu = (document.activeElement === ref.current) ||
        ref.current.contains(document.activeElement)
      if (!isFocusWithinMenu) {
        onClose()
      }
    }
    const handleKeyDown = (ev: KeyboardEvent) => {
      if (ev.key === 'Escape') {
        onClose()
      }
    }
    const handleClick = (ev: MouseEvent) => {
      if (ref.current && ev.target instanceof HTMLElement && !ref.current.contains(ev.target)) {
        onClose()
      }
    }
    window.addEventListener('focus', handleFocusChange, true)
    window.addEventListener('keydown', handleKeyDown)
    window.addEventListener('click', handleClick)
    return () => {
      window.removeEventListener('focus', handleFocusChange)
      window.removeEventListener('keydown', handleKeyDown)
      window.removeEventListener('click', handleClick)
    }
  }, [ref.current, onClose])
}
