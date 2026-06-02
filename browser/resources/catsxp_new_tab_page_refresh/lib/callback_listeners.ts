/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

type Router<T> = {
  [P in keyof T]: {
    addListener: (listener: any) => number
  }
} & {
  removeListener: (callbackId: number) => void
}

export function addCallbackListeners<T>(
  router: Router<T>,
  listeners: Partial<T>,
) {
  const callbackIds = Object.entries(listeners).map(([key, value]) => {
    return router[key as keyof T].addListener(value)
  })
  return () => {
    callbackIds.forEach((id) => router.removeListener(id))
  }
}
