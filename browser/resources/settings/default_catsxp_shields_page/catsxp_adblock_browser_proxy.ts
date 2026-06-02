/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { sendWithPromise, addWebUiListener } from 'chrome://resources/js/cr.js'

export class Scriptlet {
  name: string

  kind: object = {
    mime: 'application/javascript'
  }

  content: string
}

export interface FilterList {
  uuid: string
  url: string
  title: string
  desc: string
  support_url: string
  component_id: string
  base64_public_key: string
  enabled: boolean
}

export interface SubscriptionInfo {
  subscription_url: string
  last_update_attempt: number
  last_successful_update_attempt: number
  enabled: boolean
  title?: string
  homepage?: string
}

export enum ErrorCode {
  kOK = 0,
  kInvalidName,
  kAlreadyExists,
  kNotFound,
}

export interface CatsxpAdblockBrowserProxy {
  getRegionalLists: () => Promise<FilterList[]>
  enableFilterList: (uuid: string, enabled: boolean) => void
  updateFilterLists: () => Promise<boolean>
  getCustomFilters: () => Promise<string>
  updateCustomFilters: (value: string) => void
  getListSubscriptions: () => Promise<any>
  setSubscriptionEnabled: (url: string, enabled: boolean) => void
  addSubscription: (url: string) => void
  updateSubscription: (url: string) => void
  deleteSubscription: (url: string) => void
  viewSubscription: (url: string) => void
  getCustomScriptlets: () => Promise<Scriptlet[]>
  addCustomScriptlet: (scriptlet: Scriptlet) => Promise<ErrorCode>
  updateCustomScriptlet: (name: string, scriptlet: Scriptlet) =>
    Promise<ErrorCode>
  removeCustomScriptlet: (name: string) => Promise<ErrorCode>
  addWebUiListener: (eventName: string, callback: Function) => void
}

export class CatsxpAdblockBrowserProxyImpl implements CatsxpAdblockBrowserProxy {
  static getInstance() {
    return instance || (instance = new CatsxpAdblockBrowserProxyImpl())
  }

  getRegionalLists () {
    return sendWithPromise<FilterList[]>('catsxp_adblock.getRegionalLists')
  }

  enableFilterList (uuid: string, enabled: boolean) {
    chrome.send('catsxp_adblock.enableFilterList', [uuid, enabled])
  }

  updateFilterLists () {
    return sendWithPromise<boolean>('catsxp_adblock.updateFilterLists')
  }

  getCustomFilters () {
    return sendWithPromise<string>('catsxp_adblock.getCustomFilters')
  }

  updateCustomFilters (value: string) {
    chrome.send('catsxp_adblock.updateCustomFilters', [value])
  }

  getListSubscriptions () {
    return sendWithPromise<any>('catsxp_adblock.getListSubscriptions')
  }

  setSubscriptionEnabled (url: string, enabled: boolean) {
    chrome.send('catsxp_adblock.setSubscriptionEnabled', [url, enabled])
  }

  addSubscription (url: string) {
    chrome.send('catsxp_adblock.addSubscription', [url])
  }

  updateSubscription (url: string) {
    chrome.send('catsxp_adblock.updateSubscription', [url])
  }

  deleteSubscription (url: string) {
    chrome.send('catsxp_adblock.deleteSubscription', [url])
  }

  viewSubscription (url: string) {
    chrome.send('catsxp_adblock.viewSubscription', [url])
  }

  getCustomScriptlets () {
    return sendWithPromise<Scriptlet[]>('catsxp_adblock.getCustomScriptlets')
      .then((scriptlets) => {
        for (const scriptlet of scriptlets) {
          scriptlet.content = this.base64ToUtf8_(scriptlet.content)
        }
        return scriptlets
      })
      .catch((error) => {
        throw error
      })
  }

  addCustomScriptlet (scriptlet: Scriptlet) {
    scriptlet.content = this.utf8ToBase64_(scriptlet.content)
    return sendWithPromise<ErrorCode>('catsxp_adblock.addCustomScriptlet', scriptlet)
  }

  updateCustomScriptlet (name: string, scriptlet: Scriptlet) {
    scriptlet.content = this.utf8ToBase64_(scriptlet.content)
    return sendWithPromise<ErrorCode>(
      'catsxp_adblock.updateCustomScriptlet', name, scriptlet
    )
  }

  removeCustomScriptlet (name: string) {
    return sendWithPromise<ErrorCode>('catsxp_adblock.removeCustomScriptlet', name)
  }

  addWebUiListener (eventName: string, callback: Function) {
    addWebUiListener(eventName, callback)
  }

  private utf8ToBase64_ (str: string) {
    const uint8Array = new TextEncoder().encode(str)
    let binaryString = ''
    const chunkSize = 1024
    for (let i = 0; i < uint8Array.length; i += chunkSize) {
      const chunk = uint8Array.slice(i, i + chunkSize)
      binaryString += String.fromCharCode(...chunk)
    }
    const base64String = btoa(binaryString)
    // Replace with uint8Array.toBase64() when TypeScript adds support for 
    // toBase64 method.
    return base64String
  }

  private base64ToUtf8_ (base64: string) {
    const binaryString = atob(base64)
    const bytes = new Uint8Array(binaryString.length)
    for (let i = 0; i < binaryString.length; i++) {
      bytes[i] = binaryString.charCodeAt(i)
    }
    return new TextDecoder().decode(bytes)
  }
}

let instance: CatsxpAdblockBrowserProxy|null = null
