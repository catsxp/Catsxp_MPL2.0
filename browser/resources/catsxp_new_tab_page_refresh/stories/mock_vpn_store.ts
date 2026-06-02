/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import {
  VpnActions,
  defaultVpnStore,
  ConnectionState,
} from '../state/vpn_store'

export function createVpnStore() {
  const store = defaultVpnStore()

  store.update({
    initialized: true,
    vpnFeatureEnabled: true,
    showVpnWidget: true,
    vpnPurchased: true,
    vpnConnectionState: ConnectionState.CONNECTED,
    vpnConnectionRegion: {
      name: '',
      continent: '',
      countryIsoCode: '',
      regionPrecision: '',
      cities: [],
      latitude: 0,
      longitude: 0,
      serverCount: 0,
      isAutomatic: false,
      smartRoutingProxyState: 'none',
      country: 'Brazil',
      namePretty: 'Rio de Janeiro',
    },
  })

  const actions: VpnActions = {
    ...store.getState().actions,

    setShowVpnWidget(showVpnWidget) {
      store.update({ showVpnWidget })
    },

    toggleVpnConnection() {
      store.update((state) => {
        return {
          vpnConnectionState:
            state.vpnConnectionState === ConnectionState.CONNECTED
            || state.vpnConnectionState === ConnectionState.CONNECTING
              ? ConnectionState.DISCONNECTED
              : ConnectionState.CONNECTED,
        }
      })
    },
  }

  store.update({ actions })

  return store
}
