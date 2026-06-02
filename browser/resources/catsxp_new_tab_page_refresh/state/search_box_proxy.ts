/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as mojom from 'chrome://resources/mojo/components/omnibox/browser/searchbox.mojom-webui.js'

import { addCallbackListeners } from '../lib/callback_listeners'

let instance: SearchBoxProxy | null = null

export class SearchBoxProxy {
  callbackRouter: mojom.PageCallbackRouter
  handler: mojom.PageHandlerRemote

  constructor(
    callbackRouter: mojom.PageCallbackRouter,
    handler: mojom.PageHandlerRemote,
  ) {
    this.callbackRouter = callbackRouter
    this.handler = handler
  }

  addListeners(listeners: Partial<mojom.PageInterface>) {
    return addCallbackListeners(this.callbackRouter, listeners)
  }

  static getInstance(): SearchBoxProxy {
    if (!instance) {
      const callbackRouter = new mojom.PageCallbackRouter()
      const handler = new mojom.PageHandlerRemote()
      mojom.PageHandlerFactory.getRemote().createPageHandler(
        callbackRouter.$.bindNewPipeAndPassRemote(),
        handler.$.bindNewPipeAndPassReceiver(),
      )
      instance = new SearchBoxProxy(callbackRouter, handler)
    }
    return instance
  }
}
