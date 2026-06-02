/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import {sendWithPromise} from 'chrome://resources/js/cr.js';

export type NewTabOption = {
  name: string
  value: number // corresponds to NewTabPageShowsOptions enum
}

export interface CatsxpNewTabBrowserProxy {
  getNewTabShowsOptionsList(): Promise<NewTabOption[]>
  shouldShowNewTabDashboardSettings(): Promise<boolean>
}

export class CatsxpNewTabBrowserProxyImpl implements CatsxpNewTabBrowserProxy {
  getNewTabShowsOptionsList() {
    return sendWithPromise<NewTabOption[]>('getNewTabShowsOptionsList')
  }

  shouldShowNewTabDashboardSettings() {
    return sendWithPromise<boolean>('shouldShowNewTabDashboardSettings')
  }

  static getInstance(): CatsxpNewTabBrowserProxyImpl {
    return instance || (instance = new CatsxpNewTabBrowserProxyImpl())
  }
}

let instance: CatsxpNewTabBrowserProxyImpl|null = null
