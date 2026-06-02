/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import './catsxp_sync_code_dialog.js';
import './catsxp_sync_delete_account_dialog.js';

import {SyncStatus} from '/shared/settings/people_page/sync_browser_proxy.js';
import {I18nMixin, I18nMixinInterface} from 'chrome://resources/cr_elements/i18n_mixin.js'
import {WebUiListenerMixin, WebUiListenerMixinInterface} from 'chrome://resources/cr_elements/web_ui_listener_mixin.js';
import {DomRepeatEvent, PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';

import {BaseMixin} from '../base_mixin.js'
import {Route, Router} from '../router.js';

import {CatsxpDeviceInfo, CatsxpSyncBrowserProxy} from './catsxp_sync_browser_proxy.js';
import {getTemplate} from './catsxp_sync_configure.html.js'

/**
 * @fileoverview
 * 'settings-catsxp-sync-configure' is the set of controls which fetches, displays
 * and updates the sync configuration.
 */

const SettingsCatsxpSyncConfigureElementBase =
  I18nMixin(WebUiListenerMixin(BaseMixin(PolymerElement))) as {
    new(): PolymerElement & WebUiListenerMixinInterface & I18nMixinInterface
  }

export class SettingsCatsxpSyncConfigureElement extends SettingsCatsxpSyncConfigureElementBase {
  static get is() {
    return 'settings-catsxp-sync-configure'
  }

  static get template() {
    return getTemplate()
  }

  static get properties() {
    return {
      /**
       * The current sync status, supplied by parent element.
       * @type {!SyncStatus}
       */
      syncStatus: Object,
      /**
       * Configured sync code
       */
      syncCode: {
        type: String,
        notify: true
      },
      /**
       * List of devices in sync chain
       * @private
       */
      deviceList_: Array,
      /**
       * Sync code dialog type. Can only have 1 at a time, so use a single property.
       * 'qr' | 'words' | 'input' | 'choose' | null
       * @private
       */
      syncCodeDialogType_: String,
      /**
       * Displaying delete account dialog when true
       */
      syncDoingDeleteAccount_: {
        type: Boolean,
        value: false
      },
    };
  }

  declare private syncStatus: SyncStatus;
  declare private syncCode: string | undefined;
  declare private deviceList_: CatsxpDeviceInfo[];
  declare private syncCodeDialogType_: string | null;
  declare private syncDoingDeleteAccount_: Boolean | false;

  browserProxy_: CatsxpSyncBrowserProxy = CatsxpSyncBrowserProxy.getInstance();

  override async connectedCallback() {
    super.connectedCallback()
    const deviceList = await this.browserProxy_.getDeviceList()
    this.addWebUiListener(
      'device-info-changed', this.handleDeviceInfo_.bind(this))
    this.handleDeviceInfo_(deviceList)
  }

  handleDeviceInfo_(deviceList: CatsxpDeviceInfo[]) {
    this.deviceList_ = deviceList
  }

  getDeviceDisplayDate(device: CatsxpDeviceInfo): string {
    const displayDate = new Date(0)
    displayDate.setUTCSeconds(device.lastUpdatedTimestamp)
    return displayDate.toLocaleString()
  }

  /*
   * This only sets sync code when it is not already set. It needs to be cleared
   * when sync chain reset
   */
  async ensureSetSyncCode_() {
    if (!!this.syncCode)
      return
    const syncCode = await this.browserProxy_.getSyncCode()
    this.syncCode = syncCode
  }

  async onViewSyncCode_() {
    await this.ensureSetSyncCode_()
    this.syncCodeDialogType_ = 'words'
  }

  async onAddDevice_() {
    await this.ensureSetSyncCode_()
    this.syncCodeDialogType_ = 'choose'
  }

  onSyncCodeDialogDone_() {
    this.syncCodeDialogType_ = null
  }

  async onResetSyncChain_() {
    const messageText = this.i18n('catsxpSyncResetConfirmation')
    const shouldReset = confirm(messageText)
    if (!shouldReset) {
      return
    }
    await this.browserProxy_.resetSyncChain();
    // Clear sync code because user might use the same page to create a new sync
    // chain without reload
    this.syncCode = undefined
    const router = Router.getInstance();
    router.navigateTo((router.getRoutes() as {CATSXP_SYNC: Route}).CATSXP_SYNC);
  }

  onPermanentlyDeleteSyncAccount_() {
    // Clear sync code because after permanently deleting the chain user might
    // use the same page to create a new sync chain without reload. In worse
    // case, we will reload the sync code
    this.syncCode = undefined
    this.syncDoingDeleteAccount_ = true;
  }

  async onDeleteDevice_(e: DomRepeatEvent<CatsxpDeviceInfo>) {
    const messageText = this.i18n('catsxpSyncDeleteDeviceConfirmation')
    const shouldDeleteDevice = confirm(messageText)
    if (!shouldDeleteDevice) {
      return
    }
    const device: CatsxpDeviceInfo = e.model.item
    await this.browserProxy_.deleteDevice(device.guid);
  }

  async onRequestStopClearData_() {
    const messageText = this.i18n('catsxpSyncResetConfirmation')
    const shouldStopClear = confirm(messageText)
    if (!shouldStopClear) {
      return
    }
    await this.browserProxy_.requestStopClearData();
  }
}

customElements.define(
  SettingsCatsxpSyncConfigureElement.is, SettingsCatsxpSyncConfigureElement)
