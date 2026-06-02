/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { getLocale } from '$web-common/locale'
import { CatsxpShieldsStrings } from 'gen/components/grit/catsxp_components_webui_strings'

export type StringKey = keyof typeof CatsxpShieldsStrings

export const getString = <(key: StringKey) => string>getLocale
