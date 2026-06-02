/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as mojom from 'gen/catsxp/components/catsxp_shields/core/common/catsxp_shields_panel.mojom.m.js'

let instance: ShieldsPanelProxy | null = null

export class ShieldsPanelProxy {
  panelHandler = new mojom.PanelHandlerRemote()
  dataHandler = new mojom.DataHandlerRemote()

  constructor() {
    const factory = mojom.PanelHandlerFactory.getRemote()
    factory.createPanelHandler(
      this.panelHandler.$.bindNewPipeAndPassReceiver(),
      this.dataHandler.$.bindNewPipeAndPassReceiver(),
    )
  }

  createUIHandlerRemote(impl: mojom.UIHandlerInterface): mojom.UIHandlerRemote {
    return new mojom.UIHandlerReceiver(impl).$.bindNewPipeAndPassRemote()
  }

  static getInstance(): ShieldsPanelProxy {
    if (!instance) {
      instance = new this()
    }
    return instance
  }
}
