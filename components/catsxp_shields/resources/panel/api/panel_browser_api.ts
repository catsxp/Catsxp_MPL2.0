/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as CatsxpShields from 'gen/catsxp/components/catsxp_shields/core/common/catsxp_shields_panel.mojom.m.js'
// Provide access to all the generated types
export * from 'gen/catsxp/components/catsxp_shields/core/common/catsxp_shields_panel.mojom.m.js'
export * from 'gen/catsxp/components/catsxp_shields/core/common/shields_settings.mojom.m.js'

interface API {
  panelHandler: CatsxpShields.PanelHandlerRemote
  dataHandler: CatsxpShields.DataHandlerRemote
}

let panelBrowserAPIInstance: API
class PanelBrowserAPI implements API {
  panelHandler = new CatsxpShields.PanelHandlerRemote()
  dataHandler = new CatsxpShields.DataHandlerRemote()

  constructor () {
    const factory = CatsxpShields.PanelHandlerFactory.getRemote()
    factory.createPanelHandler(
      this.panelHandler.$.bindNewPipeAndPassReceiver(),
      this.dataHandler.$.bindNewPipeAndPassReceiver()
    )
  }
}

export default function getPanelBrowserAPI () {
  if (!panelBrowserAPIInstance) {
    panelBrowserAPIInstance = new PanelBrowserAPI()
  }
  return panelBrowserAPIInstance
}
