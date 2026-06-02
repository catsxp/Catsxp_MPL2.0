/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import { NewTabPageAdEventType } from '../../state/background_store'
import { AutocompleteMatch } from '../../state/search_store'

// This module defines the protocol for exchanging messages between the NTP and
// a rich media background iframe. Messages should only be sent to the iframe
// via the `RichMediaFrameHandle` interface. Messages coming from the iframe
// should only be processed via the `handleIncomingMessage` function.

// Messages that can be sent to a rich media background iframe.
export type RichMediaOutgoingMessage = SafeRectMessage | SearchMatchesMessage

interface SafeRectMessage {
  type: 'richMediaSafeRect'
  value: {
    x: number
    y: number
    width: number
    height: number
  }
}

interface SearchMatchesMessage {
  type: 'richMediaSearchMatches'
  value: AutocompleteMatch[]
}

// Messages that can be received from a rich media background iframe.
export type RichMediaIncomingMessage =
  | AdEventMessage
  | SearchAutocompleteMessage
  | OpenSearchMessage
  | HideCatsxpSearchBoxMessage
  | MakeCatsxpSearchDefaultMessage

interface AdEventMessage {
  type: 'richMediaEvent'
  value: NewTabPageAdEventType
}

interface SearchAutocompleteMessage {
  type: 'richMediaQueryCatsxpSearchAutocomplete'
  value: string
}

interface OpenSearchMessage {
  type: 'richMediaOpenCatsxpSearchWithQuery'
  value: string
}

interface HideCatsxpSearchBoxMessage {
  type: 'richMediaHideCatsxpSearchBox'
}

interface MakeCatsxpSearchDefaultMessage {
  type: 'richMediaMakeCatsxpSearchDefault'
}

// The interface through which messages can be sent to a rich media background
// frame.
export interface RichMediaFrameHandle {
  postMessage: (message: RichMediaOutgoingMessage) => void
}

// The set of capabilities exposed by the NTP to the rich media background
// iframe.
export interface RichMediaCapabilities {
  notifyAdEvent: (eventType: NewTabPageAdEventType) => void
  openDestinationUrl: () => void
  openCatsxpSearch: (pathAndQuery: string) => void
  queryCatsxpSearchAutocomplete: (query: string) => void
  hideCatsxpSearchBox: () => void
  makeCatsxpSearchDefault: () => void
}

// Takes a raw incoming rich media message and executes the appropriate
// capability.
export function handleIncomingMessage(
  data: unknown,
  capabilities: RichMediaCapabilities,
) {
  const message = readIncomingMessage(data)
  if (!message) {
    console.warn('Invalid rich media message', data)
    return
  }
  dispatchIncomingMessage(message, capabilities)
}

// Reads a rich media message posted from the background iframe. Exported for
// testing.
export function readIncomingMessage(
  data: any,
): RichMediaIncomingMessage | null {
  if (!data) {
    return null
  }
  const { type } = data
  switch (type) {
    case 'richMediaEvent': {
      const value = parseAdEventType(data.value)
      return value !== null ? { type, value } : null
    }
    case 'richMediaQueryCatsxpSearchAutocomplete': {
      return data.value ? { type, value: String(data.value) } : null
    }
    case 'richMediaOpenCatsxpSearchWithQuery': {
      return data.value ? { type, value: String(data.value) } : null
    }
    case 'richMediaHideCatsxpSearchBox': {
      return { type }
    }
    case 'richMediaMakeCatsxpSearchDefault': {
      return { type }
    }
  }
  return null
}

function parseAdEventType(data: any): NewTabPageAdEventType | null {
  switch (data) {
    case 'click':
      return NewTabPageAdEventType.kClicked
    case 'interaction':
      return NewTabPageAdEventType.kInteraction
    case 'mediaPlay':
      return NewTabPageAdEventType.kMediaPlay
    case 'media25':
      return NewTabPageAdEventType.kMedia25
    case 'media100':
      return NewTabPageAdEventType.kMedia100
  }
  return null
}

// Takes an incoming rich media message and executes the appropriate capability.
// Exported for testing. Clients should use `handleIncomingMessage`.
export function dispatchIncomingMessage(
  message: RichMediaIncomingMessage,
  capabilities: RichMediaCapabilities,
) {
  switch (message.type) {
    case 'richMediaEvent': {
      capabilities.notifyAdEvent(message.value)
      if (message.value === NewTabPageAdEventType.kClicked) {
        capabilities.openDestinationUrl()
      }
      break
    }
    case 'richMediaOpenCatsxpSearchWithQuery': {
      capabilities.notifyAdEvent(NewTabPageAdEventType.kClicked)
      capabilities.openCatsxpSearch(message.value)
      break
    }
    case 'richMediaQueryCatsxpSearchAutocomplete': {
      capabilities.queryCatsxpSearchAutocomplete(message.value)
      break
    }
    case 'richMediaHideCatsxpSearchBox': {
      capabilities.hideCatsxpSearchBox()
      break
    }
    case 'richMediaMakeCatsxpSearchDefault': {
      capabilities.makeCatsxpSearchDefault()
      break
    }
  }
}
