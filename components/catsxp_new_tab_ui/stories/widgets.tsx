/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { Provider } from 'react-redux'
import { createStore } from 'redux'
import { select, withKnobs } from '@storybook/addon-knobs'
import {
  VPNPromoWidget,
  VPNMainWidget
} from '../components/default/vpn/vpn_card'
import * as CatsxpVPN from '../api/catsxpVpn'
import '../../catsxp_vpn/resources/panel/stories/locale'
import {
  mockRegionList
} from '../../catsxp_vpn/resources/panel/stories/mock-data/region-list'

export default {
  title: 'VPN/Card',
  decorators: [
    (Story: any) => {
      const store = createStore((state) => state)
      return (
        <Provider store={store}>
          <Story />
        </Provider>
      )
    },
    withKnobs
  ]
}

export const VPNPromo = () => <VPNPromoWidget />

export const VPNMain = () => (
  <VPNMainWidget
    connectionState={select(
      'connection state',
      CatsxpVPN.ConnectionState,
      CatsxpVPN.ConnectionState.DISCONNECTED
    )}
    selectedRegion={mockRegionList[0]}
  />
)
