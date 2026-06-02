/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

interface CSSVars {
  [key: `--${string}`]: string | number
}

// Allows a collection of CSS custom variables to be used in the "style" prop of
// React components.
export function inlineCSSVars(vars: CSSVars) {
  return vars as React.CSSProperties
}
