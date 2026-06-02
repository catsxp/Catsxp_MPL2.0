/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { withKnobs, text } from '@storybook/addon-knobs'
import ThemeProvider from '../../common/CatsxpCoreThemeProvider'
import CatsxpNewsLoadingCard from '../components/default/catsxpNews/cards/cardLoading'
import CatsxpNewsErrorCard from '../components/default/catsxpNews/cards/cardError'
import PublisherMeta from '../components/default/catsxpNews/cards/PublisherMeta'
import * as CatsxpNews from '../../catsxp_news/browser/resources/shared/api'

const onClick = () => alert('clicked')

export default {
  title: 'New Tab/Catsxp News',
  decorators: [
    (Story: any) => <ThemeProvider><Story /></ThemeProvider>,
    (Story: any) => (
      <div
        style={{
          display: 'flex',
          fontFamily: 'Poppins',
          alignItems: 'center',
          justifyContent: 'center',
          gap: '20px',
          width: '100%',
          minHeight: '100vh',
          background: 'url(https://placekitten.com/2000/3000)',
          backgroundSize: 'contain',
          color: 'pink',
          fontSize: '22px',
          fontWeight: 600
        }}
      >
        <Story />
      </div>
    ),
    withKnobs
  ]
}

export const Publisher = () => (
  <>
    <PublisherMeta
      publisher={{
        publisherId: '123abc',
        publisherName: text('Publisher Name', 'small'),
        categoryName: 'Top News',
        feedSource: { url: 'http://www.example.com/feed' },
        backgroundColor: undefined,
        coverUrl: undefined,
        faviconUrl: undefined,
        siteUrl: { url: 'https://www.example.com' },
        locales: [{
          locale: 'en_US',
          rank: 0,
          channels: ['Top News', 'Top Sources']
        }],
        type: CatsxpNews.PublisherType.COMBINED_SOURCE,
        isEnabled: true,
        userEnabledStatus: CatsxpNews.UserEnabled.NOT_MODIFIED
      }}
      onSetPublisherPref={onClick}
    />
    <PublisherMeta
      publisher={{
        publisherId: '123abcdef',
        publisherName: text('Publisher Name 2', 'The Miller Chronicle'),
        categoryName: 'Top News',
        feedSource: { url: 'http://www.example.com/feed' },
        backgroundColor: undefined,
        coverUrl: undefined,
        faviconUrl: undefined,
        siteUrl: { url: 'https://www.example.com' },
        locales: [{
          locale: 'en_US',
          rank: 0,
          channels: ['Top News', 'Top Sources']
        }],
        type: CatsxpNews.PublisherType.COMBINED_SOURCE,
        isEnabled: true,
        userEnabledStatus: CatsxpNews.UserEnabled.NOT_MODIFIED
      }}
      onSetPublisherPref={onClick}
    />
  </>
)

export const Loading = () => (
  <CatsxpNewsLoadingCard />
)

export const Error = () => (
  <CatsxpNewsErrorCard onRefresh={() => console.log('refresh clicked')} />
)

