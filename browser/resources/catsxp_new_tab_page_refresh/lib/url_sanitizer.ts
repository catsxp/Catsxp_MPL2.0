/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

const allowedProtocols = new Set(['https:', 'chrome:'])

export function sanitizeExternalURL(urlString: string) {
  let url: URL | null = null
  try {
    url = new URL(urlString)
  } catch {
    return ''
  }
  if (!allowedProtocols.has(url.protocol)) {
    return ''
  }
  return url.toString()
}
