/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { createAction } from 'redux-act'
import * as CatsxpVPN from '../api/catsxpVpn'

export const initialize = createAction<CatsxpVPN.PurchasedState>('initialize')
export const toggleConnection = createAction('toggleConnection')
export const launchVPNPanel = createAction('launchVPNPanel')
export const openVPNAccountPage =
  createAction<CatsxpVPN.ManageURLType>('openVPNAccountPage')
export const purchasedStateChanged = createAction<CatsxpVPN.PurchasedState>(
  'purchasedStateChanged'
)
export const connectionStateChanged = createAction<CatsxpVPN.ConnectionState>(
  'connectionStateChanged'
)
export const selectedRegionChanged = createAction<CatsxpVPN.Region>(
  'connectionStateChanged'
)
