/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import wallpaperImageUrl from '../../../../img/newtab/dummy-branded-wallpaper/background-1.jpg'
import brandingImageUrl from '../../../../img/newtab/dummy-branded-wallpaper/logo.png'
import { NewTabPageAdMetricType } from 'gen/catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.m.js'

const dummyWallpaper: NewTab.BrandedWallpaper = {
  type: 'image',
  wallpaperImageUrl,
  isSponsored: true,
  creativeInstanceId: '12345abcde',
  metricType: NewTabPageAdMetricType.kConfirmation,
  wallpaperId: 'abcde12345',
  logo: {
    image: brandingImageUrl,
    companyName: 'Technikke',
    alt: 'Technikke: For music lovers.',
    destinationUrl: 'https://catsxp.com'
  }
}

export default dummyWallpaper
