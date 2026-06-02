/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { sendWithPromise } from 'chrome://resources/js/cr.js'

export type ContactInfo = {
  contactInfo: string | null
  contactInfoSaveFlag: boolean
}

export interface DefaultCatsxpShieldsBrowserProxy {
  isAdControlEnabled: () => Promise<boolean>
  setAdControlType: (value: boolean) => void

  isFirstPartyCosmeticFilteringEnabled: () => Promise<boolean>
  setCosmeticFilteringControlType: (value: string) => void

  getCookieControlType: () => Promise<string>
  setCookieControlType: (value: string) => void

  getFingerprintingControlType: () => Promise<string>
  setFingerprintingControlType: (value: string) => void

  getFingerprintingBlockEnabled: () => Promise<boolean>
  setFingerprintingBlockEnabled: (value: boolean) => void

  getHttpsUpgradeControlType: () => Promise<string>
  setHttpsUpgradeControlType: (value: string) => void

  getNoScriptControlType: () => Promise<boolean>
  setNoScriptControlType: (value: boolean) => void

  getForgetFirstPartyStorageEnabled: () => Promise<boolean>
  setForgetFirstPartyStorageEnabled: (value: boolean) => void

  setContactInfoSaveFlag: (value: boolean) => void
  getContactInfo: () => Promise<ContactInfo>

  getHideBlockAllCookieTogle: () => Promise<boolean>

  getAllowElementBlockerInPrivateModeEnabled: () => Promise<boolean>
  setAllowElementBlockerInPrivateModeEnabled: (value: boolean) => void

  loadShieldManager: (value: string) => void

  getCustomRule: (value: string) => Promise<string>

  setCustomRule: (type: string, value: string) => Promise<boolean>
}

export class DefaultCatsxpShieldsBrowserProxyImpl
implements DefaultCatsxpShieldsBrowserProxy {
  isAdControlEnabled () {
    return sendWithPromise<boolean>('isAdControlEnabled')
  }

  setAdControlType (value: boolean) {
    chrome.send('setAdControlType', [value])
  }

  isFirstPartyCosmeticFilteringEnabled () {
    return sendWithPromise<boolean>('isFirstPartyCosmeticFilteringEnabled')
  }

  setCosmeticFilteringControlType (value: string) {
    chrome.send('setCosmeticFilteringControlType', [value])
  }

  getCookieControlType () {
    return sendWithPromise<string>('getCookieControlType')
  }

  setCookieControlType (value: string) {
    chrome.send('setCookieControlType', [value])
  }

  getFingerprintingControlType () {
    return sendWithPromise<string>('getFingerprintingControlType')
  }

  setFingerprintingControlType (value: string) {
    chrome.send('setFingerprintingControlType', [value])
  }

  getFingerprintingBlockEnabled () {
    return sendWithPromise<boolean>('getFingerprintingBlockEnabled')
  }

  setFingerprintingBlockEnabled (value: boolean) {
    chrome.send('setFingerprintingBlockEnabled', [value])
  }

  getHttpsUpgradeControlType () {
    return sendWithPromise<string>('getHttpsUpgradeControlType')
  }

  setHttpsUpgradeControlType (value: string) {
    chrome.send('setHttpsUpgradeControlType', [value])
  }

  getNoScriptControlType () {
    return sendWithPromise<boolean>('getNoScriptControlType')
  }

  setNoScriptControlType (value: boolean) {
    chrome.send('setNoScriptControlType', [value])
  }

  getForgetFirstPartyStorageEnabled () {
    return sendWithPromise<boolean>('getForgetFirstPartyStorageEnabled')
  }

  setForgetFirstPartyStorageEnabled (value: boolean) {
    chrome.send('setForgetFirstPartyStorageEnabled', [value])
  }

  setContactInfoSaveFlag (value: boolean) {
    chrome.send('setContactInfoSaveFlag', [value])
  }

  getContactInfo () {
    return sendWithPromise<ContactInfo>('getContactInfo')
  }

  getHideBlockAllCookieTogle () {
    return sendWithPromise<boolean>('getHideBlockAllCookieTogle')
  }

  getAllowElementBlockerInPrivateModeEnabled () {
    return sendWithPromise<boolean>('getAllowElementBlockerInPrivateModeEnabled')
  }
  setAllowElementBlockerInPrivateModeEnabled (value: boolean) {
    chrome.send('setAllowElementBlockerInPrivateModeEnabled', [value])
  }

  loadShieldManager(value: string) {
    chrome.send('loadShieldManager', [value]);
  }

  getCustomRule(value: string) {
    return sendWithPromise<string>('getCustomRule', value);
  }

  setCustomRule(type: string, value: string) {
    return sendWithPromise<boolean>('setCustomRule', type, value);
  }

  static getInstance(): DefaultCatsxpShieldsBrowserProxy {
    return instance || (instance = new DefaultCatsxpShieldsBrowserProxyImpl())
  }
}


let instance: DefaultCatsxpShieldsBrowserProxy | null = null