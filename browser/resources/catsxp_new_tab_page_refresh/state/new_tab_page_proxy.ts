/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import * as mojom from 'gen/catsxp/browser/ui/webui/catsxp_new_tab_page_refresh/catsxp_new_tab_page.mojom.m.js'

import { addCallbackListeners } from '../lib/callback_listeners'

let instance: NewTabPageProxy | null = null

export class NewTabPageProxy {
  callbackRouter: mojom.NewTabPageCallbackRouter
  handler: mojom.NewTabPageHandlerRemote

  constructor(
    callbackRouter: mojom.NewTabPageCallbackRouter,
    handler: mojom.NewTabPageHandlerRemote,
  ) {
    this.callbackRouter = callbackRouter
    this.handler = handler
  }

  addListeners(listeners: Partial<mojom.NewTabPageInterface>) {
    return addCallbackListeners(this.callbackRouter, listeners)
  }

  static getInstance(): NewTabPageProxy {
    if (!instance) {
      const callbackRouter = new mojom.NewTabPageCallbackRouter()
      const handler = mojom.NewTabPageHandler.getRemote()
      handler.setNewTabPage(callbackRouter.$.bindNewPipeAndPassRemote())
      instance = new NewTabPageProxy(callbackRouter, handler)
    }
    return instance
  }
}
