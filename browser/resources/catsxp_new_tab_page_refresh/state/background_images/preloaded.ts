/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { CatsxpBackground } from '../background_store'
import * as preloadedData from './preloaded.json'

// Pre-loaded background image resources that can be used if a new profile opens
// the NTP before the NTPBackgroundImagesService has finished loading the
// current collection of Catsxp backgrounds.
export const preloadedBackgrounds: CatsxpBackground[] = preloadedData
