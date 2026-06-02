/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { loadTimeData } from '$web-common/loadTimeData'
import { radius } from "@catsxp/leo/tokens/css/variables"

// You can obtain one at https://mozilla.org/MPL/2.0/.
export const ENABLED_SEARCH_ENGINES_KEY = 'search-engines'
export const LAST_SEARCH_ENGINE_KEY = 'last-search-engine'
export const catsxpSearchHost = 'search.catsxp.com'
export const defaultSearchHost = loadTimeData.getString(
  'searchWidgetDefaultHost')
export const searchBoxRadius = radius.xl
