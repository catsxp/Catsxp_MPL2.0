/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

export default function performSideEffectLoader (storage: NewTab.State) {
  type SideEffectFunction = (currentState: NewTab.State) => void

  return function (fn: SideEffectFunction): void {
    window.setTimeout(() => fn(storage), 0)
  }
}
