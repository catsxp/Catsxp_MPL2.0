/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { CHANGE } from '@storybook/addon-knobs'
import { addons } from '@storybook/manager-api'

import { images, solidColorsForBackground, gradientColorsForBackground } from '../../../data/backgrounds'

const addonsChannel = addons.getChannel()

const generateWallpapers = function (images: NewTab.BackgroundWallpaper[],
  solidColors: NewTab.ColorBackground[],
  gradientColors: NewTab.ColorBackground[]) {
  let staticImages = { defaultImage: undefined }
  for (const image of images) {
    // author is optional field.
    if (image.type !== 'catsxp' || !image.author) {
      continue
    }

    Object.assign(staticImages, {
      [image.author]: {
        ...image,
        // eslint-disable-next-line @typescript-eslint/no-require-imports
        wallpaperImageUrl: require('../../../../img/newtab/backgrounds/' + image.wallpaperImageUrl)
      }
    })

    if (!staticImages.defaultImage) {
      staticImages.defaultImage = staticImages[image.author as keyof typeof staticImages]
    }
  }

  const reducer = (prev: any, colorBackground: NewTab.ColorBackground) => {
    return {
      ...prev,
      [colorBackground.wallpaperColor]: colorBackground
    }
  }

  staticImages = solidColors.reduce(reducer, staticImages)
  staticImages = gradientColors.reduce(reducer, staticImages)

  return staticImages
}.bind(null, images, solidColorsForBackground, gradientColorsForBackground)

export const backgroundWallpapers = generateWallpapers()

/**
 * Mock handler for colored backgrounds. Emits a change event to knobs
 * @param {string} value
 */
export const onChangeColoredBackground = (value: string, useRandomValue: boolean) => {
  addonsChannel.emit(CHANGE, {
    name: 'Show branded background image?',
    value: false
  })
  addonsChannel.emit(CHANGE, {
    name: 'Background',
    value: backgroundWallpapers[value]
  })
}

/**
 * Mock handler for Catsxp background. Emits a change event to knobs.
 * @param {string} selectedBackground - selected background URL
 * in storybook, we have only one preset image.
 */
export const onUseCatsxpBackground = (selectedBackground: string) => {
  addonsChannel.emit(CHANGE, {
    name: 'Background',
    value: backgroundWallpapers.defaultImage
  })
}

export const onShowBrandedImageChanged = (show: boolean) => {
  addonsChannel.emit(CHANGE, {
    name: 'Show branded background image?',
    value: show
  })
}
