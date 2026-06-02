/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { CatsxpVPNState } from '../../../reducers/catsxp_vpn'
import * as CatsxpVPN from '../../../api/catsxpVpn'

export default function getCatsxpVPNState (): CatsxpVPNState {
  return {
    purchasedState: CatsxpVPN.PurchasedState.NOT_PURCHASED,
    connectionState: CatsxpVPN.ConnectionState.DISCONNECTED,
    selectedRegion: new CatsxpVPN.Region()
  }
}
