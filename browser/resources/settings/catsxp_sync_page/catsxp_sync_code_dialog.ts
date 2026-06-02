/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import '../settings_shared.css.js';

import 'chrome://resources/cr_elements/cr_dialog/cr_dialog.js';
import 'chrome://resources/cr_elements/cr_button/cr_button.js';
import 'chrome://resources/cr_elements/cr_icon_button/cr_icon_button.js';

import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';
import {I18nMixin, I18nMixinInterface} from 'chrome://resources/cr_elements/i18n_mixin.js'
import {BaseMixin} from '../base_mixin.js'
import {CatsxpSyncBrowserProxy} from './catsxp_sync_browser_proxy.js';
import {getTemplate} from './catsxp_sync_code_dialog.html.js'

/**
 * @fileoverview
 * 'settings-catsxp-sync-code-dialog' contains the dialog for displaying or
 * inputting the sync code. It can display in input mode or in read-only
 * words, qr-code, or a 'chooser' which will allow the user to choose words or
 * qr-code.
 */

const SettingsCatsxpSyncCodeDialogElementBase =
  I18nMixin(BaseMixin(PolymerElement)) as {
    new(): PolymerElement & I18nMixinInterface
  }

export class SettingsCatsxpSyncCodeDialogElement extends SettingsCatsxpSyncCodeDialogElementBase {
  static get is() {
    return 'settings-catsxp-sync-code-dialog'
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
       * 'qr' | 'words' | 'choose' | 'input'
       */
      codeType: {
        type: String,
        value: 'choose',
        notify: true
      },
      syncCodeValidationError: {
        type: String,
        value: '',
        notify: true
      },
      syncCodeWordCount_: {
        type: Number,
        value: 0
      },
      hasCopiedSyncCode_: {
        type: Boolean,
        value: false
      },
      qrCodeImageUrl_: {
        type: String,
        value: null
      },
    };
  }

  static get observers() {
    return [
      'getQRCode_(syncCode, codeType)',
      'computeSyncCodeWordCount_(syncCode, codeType)',
    ];
  }

  private declare syncCode: string | undefined;
  private declare codeType: 'qr' | 'words' | 'choose' | 'input' | null;
  private declare syncCodeValidationError: string;
  private declare syncCodeWordCount_: number;
  private declare hasCopiedSyncCode_: boolean;
  private declare qrCodeImageUrl_: string;
  private hasCopiedSyncCodeTimer_: ReturnType<typeof window.setTimeout>;

  syncBrowserProxy_: CatsxpSyncBrowserProxy = CatsxpSyncBrowserProxy.getInstance();

  async computeSyncCodeWordCount_() {
    if (this.codeType !== 'words' && this.codeType !== 'input') {
      return
    }

    this.syncCodeWordCount_ =
      await this.syncBrowserProxy_.getWordsCount(this.syncCode ?? '')
  }

  isCodeType(askingType: string) {
    return (this.codeType === askingType)
  }

  handleClose_() {
    this.codeType = null
    this.syncCodeValidationError = ''
  }

  handleChooseMobile_() {
    this.codeType = null
    window.setTimeout(() => {
      this.codeType = 'qr'
    }, 0)
  }

  handleChooseComputer_() {
    this.codeType = null
    window.setTimeout(() => {
      this.codeType = 'words'
    }, 0)
  }

  async handleSyncCodeCopy_() {
    if (!this.syncCode) {
      console.warn('Skip handleSyncCodeCopy because code words are empty')
      return
    }
    window.clearTimeout(this.hasCopiedSyncCodeTimer_)
    try {
      await this.syncBrowserProxy_.copySyncCodeToClipboard(this.syncCode)
    } catch (e) {
      console.error('copySyncCodeToClipboard failed', e)
    }
    this.hasCopiedSyncCode_ = true
    this.hasCopiedSyncCodeTimer_ = window.setTimeout(() => {
      this.hasCopiedSyncCode_ = false
    }, 4000)
  }

  handleDone_() {
    this.dispatchEvent(new CustomEvent('done'))
  }

  async getQRCode_() {
    if (this.codeType !== 'qr') {
      return
    }
    if (!this.syncCode) {
      console.warn('Skip getQRCode because code words are empty')
      return
    }
    try {
      this.qrCodeImageUrl_ = await this.syncBrowserProxy_.getQRCode(this.syncCode)
    } catch (e) {
      console.error('getQRCode failed', e)
    }
  }
}

customElements.define(
  SettingsCatsxpSyncCodeDialogElement.is, SettingsCatsxpSyncCodeDialogElement)
