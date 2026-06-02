/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { getLocale } from '$web-common/locale'
import '$web-common/strings'

import {
  CatsxpNewsStrings,
  CatsxpNewTabPageStrings,
  CatsxpOmniboxStrings,
} from 'gen/components/grit/catsxp_components_webui_strings'

declare global {
  interface Strings {
    CatsxpNewTabPageStrings: typeof CatsxpNewTabPageStrings
    CatsxpOmniboxStrings: typeof CatsxpOmniboxStrings
  }
}

export type StringKey =
  | CatsxpNewTabPageStrings
  | CatsxpNewsStrings
  | CatsxpOmniboxStrings

export function getString(key: StringKey) {
  return getLocale(key)
}

