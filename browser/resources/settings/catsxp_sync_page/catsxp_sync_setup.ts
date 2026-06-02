/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import './catsxp_sync_code_dialog.js';

import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';
import {I18nMixin, I18nMixinInterface} from 'chrome://resources/cr_elements/i18n_mixin.js'
import {BaseMixin} from '../base_mixin.js'
import {CatsxpSyncBrowserProxy} from './catsxp_sync_browser_proxy.js';
import {getTemplate} from './catsxp_sync_setup.html.js'

/**
 * @fileoverview
 * 'catsxp-sync-setup' is the UI for starting or joining a sync chain
 * settings.
 */

const SettingsCatsxpSyncSetupElementBase =
  I18nMixin(BaseMixin(PolymerElement)) as {
    new(): PolymerElement & I18nMixinInterface
  }

export class SettingsCatsxpSyncSetupElement extends SettingsCatsxpSyncSetupElementBase {
  static get is() {
    return 'settings-catsxp-sync-setup'
  }

  static get template() {
    return getTemplate()
  }

  static get properties() {
    return {
      syncCode: {
        type: String,
        notify: true
      },
      /**
      * Sync code dialog type. Can only have 1 at a time, so use a single property.
      * 'qr' | 'words' | 'input' | 'choose' | null
      */
      syncCodeDialogType: {
        type: String,
        notify: true,
      },
      isSubmittingSyncCode_: {
        type: Boolean,
        value: false,
      },
      isGettingSyncCode_: {
        type: Boolean,
        value: false,
      },
      syncCodeValidationError_: {
        type: String,
        value: '',
      }
    };
  }

  private declare syncCode: string | undefined;
  private declare syncCodeDialogType: 'qr' | 'words' | 'input' | 'choose' | null;
  private declare isSubmittingSyncCode_: boolean;
  private declare isGettingSyncCode_: boolean;
  private declare syncCodeValidationError_: string;

  syncBrowserProxy_: CatsxpSyncBrowserProxy = CatsxpSyncBrowserProxy.getInstance();

  async handleStartSyncChain_() {
    this.isGettingSyncCode_ = true
    const syncCode = await this.syncBrowserProxy_.getSyncCode()
    this.isGettingSyncCode_ = false
    this.syncCode = syncCode;
    this.syncCodeDialogType = 'choose'
  }

  handleJoinSyncChain_() {
    this.syncCode = undefined
    this.syncCodeDialogType = 'input'
  }

  handleSyncCodeDialogDone_() {
    if (this.syncCodeDialogType === 'input') {
      const messageText = this.i18n('catsxpSyncFinalSecurityWarning')
      const shouldProceed = confirm(messageText)
      if (!shouldProceed) {
        return
      }
    }

    this.submitSyncCode_()
  }

  async submitSyncCode_() {
    this.isSubmittingSyncCode_ = true
    const syncCodeToSubmit = this.syncCode || ''
    let success = false
    try {
      success = await this.syncBrowserProxy_.setSyncCode(syncCodeToSubmit)
    } catch (e: unknown) {
      this.syncCodeValidationError_ = (e as string)
      success = false
    }
    this.isSubmittingSyncCode_ = false
    if (success) {
      this.syncCodeDialogType = null
      this.dispatchEvent(new CustomEvent('setup-success'))
    }
  }
}

customElements.define(
  SettingsCatsxpSyncSetupElement.is, SettingsCatsxpSyncSetupElement)
