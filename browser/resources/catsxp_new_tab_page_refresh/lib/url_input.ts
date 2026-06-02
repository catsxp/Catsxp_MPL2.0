/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

export function urlFromInput(input: string) {
  if (/\s/.test(input)) {
    return null
  }
  const bits = input.split('.')
  if (bits.length <= 1 || bits.join('').length === 0) {
    return null
  }
  if (!input.includes('://')) {
    input = `https://${input}`
  }
  const schemes = new Set(['http:', 'https:'])
  try {
    const url = new URL(input)
    if (!schemes.has(url.protocol)) {
      return null
    }
    return url
  } catch {
    return null
  }
}
