/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'
import { ReadFeedItemPayload } from '../../../actions/today_actions'
import { OnReadFeedItem } from './'

export default function useReadArticleClickHandler (action: OnReadFeedItem, payloadData: ReadFeedItemPayload) {
  return React.useCallback((e: React.MouseEvent) => {
    e.preventDefault()
    const shouldOpenInNewTab = detectShouldOpenInNewTab(e)
    action({ ...payloadData, openInNewTab: shouldOpenInNewTab })
  }, [action, payloadData.item])
}

export function detectShouldOpenInNewTab (e: React.MouseEvent): boolean {
  const openInNewTab = e.ctrlKey || e.metaKey
  return openInNewTab
}
