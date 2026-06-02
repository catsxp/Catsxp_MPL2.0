/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import {
  BackgroundStore,
  BackgroundActions,
  NewTabPageAdMetricType,
  SelectedBackgroundType,
  defaultBackgroundStore,
} from '../state/background_store'

function delay(ms: number) {
  return new Promise((resolve) => {
    setTimeout(resolve, ms)
  })
}

const sampleBackground =
  'https://catsxp.com/static-assets/images/coding-background-texture.jpg'

const sponsoredBackgrounds = {
  image: {
    wallpaperType: '',
    imageUrl: sampleBackground,
    campaignId: '1234',
    creativeInstanceId: '',
    wallpaperId: '',
    logo: {
      alt: 'Be Catsxp!',
      destinationUrl: 'https://catsxp.com',
      imageUrl: sampleBackground,
    },
    metricType: NewTabPageAdMetricType.kConfirmation,
  },

  richMedia: {
    wallpaperType: 'richMedia',
    imageUrl: './ntp-assets/fake_rich_media_background.html',
    campaignId: '1234',
    creativeInstanceId: '',
    wallpaperId: '',
    logo: {
      alt: 'Be Catsxp!',
      destinationUrl: 'https://catsxp.com',
      imageUrl: '',
    },
    metricType: NewTabPageAdMetricType.kConfirmation,
  },

  none: null,
}

export function createBackgroundStore() {
  const store = defaultBackgroundStore()

  store.update({
    initialized: true,
    catsxpBackgrounds: [
      {
        author: 'John Doe',
        imageUrl: sampleBackground,
        link: 'https://catsxp.com',
      },
    ],
    backgroundRandomValue: Math.random(),
    sponsoredImageBackground: sponsoredBackgrounds.none,
  })

  store.update({
    sponsoredRichMediaBaseUrl: location.origin,
  })

  const actions: BackgroundActions = {
    ...store.getState().actions,

    setBackgroundsEnabled(enabled) {
      store.update({ backgroundsEnabled: enabled })
    },

    setSponsoredImagesEnabled(enabled) {
      store.update({ sponsoredImagesEnabled: enabled })
    },

    selectBackground(type, value) {
      store.update({
        selectedBackground: { type, value },
        backgroundRandomValue: Math.random(),
      })
    },

    async showCustomBackgroundChooser() {
      delay(200).then(() => {
        store.update((state) => ({
          customBackgrounds: [...state.customBackgrounds, sampleBackground],
          selectedBackground: {
            type: SelectedBackgroundType.kCustom,
            value: sampleBackground,
          },
        }))
      })

      return true
    },

    async removeCustomBackground(background) {
      store.update((state) => ({
        customBackgrounds: state.customBackgrounds.filter(
          (elem) => elem !== background,
        ),
      }))
    },

    notifySponsoredImageLoadError() {},

    notifySponsoredImageLogoClicked() {},

    notifySponsoredRichMediaEvent(type) {
      console.log('richMediaEvent', type)
    },
  }

  store.update({ actions })

  return store
}

export function updateSponsoredBackground(
  store: BackgroundStore,
  type: 'none' | 'image' | 'rich',
) {
  store.update({
    sponsoredImageBackground:
      type === 'rich'
        ? sponsoredBackgrounds.richMedia
        : type === 'image'
          ? sponsoredBackgrounds.image
          : sponsoredBackgrounds.none,
  })
}
