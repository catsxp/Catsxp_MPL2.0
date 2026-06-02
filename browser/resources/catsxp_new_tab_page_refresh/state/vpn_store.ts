/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { StateStore, createStateStore } from '$web-common/state_store'

import {
  ConnectionState,
  Region,
} from 'gen/catsxp/components/catsxp_vpn/common/mojom/catsxp_vpn.mojom.m'

export { ConnectionState, Region }

export interface VpnState {
  initialized: boolean
  vpnFeatureEnabled: boolean
  showVpnWidget: boolean
  vpnPurchased: boolean
  vpnConnectionState: ConnectionState
  vpnConnectionRegion: Region | null
  actions: VpnActions
}

export type VpnStore = StateStore<VpnState>

export function defaultVpnStore(): VpnStore {
  return createStateStore<VpnState>({
    initialized: false,
    vpnFeatureEnabled: false,
    showVpnWidget: false,
    vpnPurchased: false,
    vpnConnectionState: ConnectionState.DISCONNECTED,
    vpnConnectionRegion: null,
    actions: {
      setShowVpnWidget(showVpnWidget) {},
      startVpnTrial() {},
      restoreVpnPurchase() {},
      toggleVpnConnection() {},
      openVpnPanel() {},
    },
  })
}

export interface VpnActions {
  setShowVpnWidget: (showVpnWidget: boolean) => void
  startVpnTrial: () => void
  restoreVpnPurchase: () => void
  toggleVpnConnection: () => void
  openVpnPanel: () => void
}
