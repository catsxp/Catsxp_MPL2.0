/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { SyncStatus } from '/shared/settings/people_page/sync_browser_proxy.js';
import { sendWithPromise } from 'chrome://resources/js/cr.js';

export type CatsxpDeviceInfo = {
  name: string
  guid: string
  id: string
  os: string
  type: string
  chromeVersion: string
  lastUpdatedTimestamp: number
  sendTabToSelfReceivingEnabled: boolean
  supportsSelfDelete: boolean
  isCurrentDevice: boolean
  hasSharingInfo: boolean
}

export interface CatsxpSyncStatus extends SyncStatus {
  hasSyncWordsDecryptionError: boolean
  isOsEncryptionAvailable: boolean
}

export class CatsxpSyncBrowserProxy {
  getSyncCode(): Promise<string> {
    return sendWithPromise('SyncSetupGetSyncCode');
  }

  getPureSyncCode(): Promise<string> {
    return sendWithPromise('SyncSetupGetPureSyncCode');
  }

  getQRCode(syncCode: string): Promise<string> {
    return sendWithPromise('SyncGetQRCode', syncCode);
  }

  copySyncCodeToClipboard(syncCode: string): Promise<boolean> {
    return sendWithPromise('SyncCopySyncCodeToClipboard', syncCode);
  }

  getDeviceList(): Promise<CatsxpDeviceInfo[]> {
    return sendWithPromise('SyncGetDeviceList');
  }

  setSyncCode(syncCode: string): Promise<boolean> {
    return sendWithPromise('SyncSetupSetSyncCode', syncCode);
  }

  resetSyncChain(): Promise<boolean> {
    return sendWithPromise('SyncSetupReset');
  }

  deleteDevice(deviceId: string): Promise<boolean> {
    return sendWithPromise('SyncDeleteDevice', deviceId);
  }

  getSyncStatus(): Promise<CatsxpSyncStatus> {
    return sendWithPromise('SyncSetupGetSyncStatus');
  }

  permanentlyDeleteSyncAccount(): Promise<boolean> {
    return sendWithPromise('SyncPermanentlyDeleteAccount');
  }

  requestStopClearData(): Promise<void> {
    return sendWithPromise('SyncStopClearData');
  }

  getWordsCount(syncCode: string): Promise<number> {
    return sendWithPromise('SyncGetWordsCount', syncCode);
  }
  static getInstance() {
    return instance || (instance = new CatsxpSyncBrowserProxy())
  }
}

let instance: CatsxpSyncBrowserProxy | null = null
