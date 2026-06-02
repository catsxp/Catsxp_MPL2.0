/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import '../settings_shared.css.js';

import {PrefsMixin} from '/shared/settings/prefs/prefs_mixin.js';
import {I18nMixin} from 'chrome://resources/cr_elements/i18n_mixin.js';
import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';

import {BaseMixin} from '../base_mixin.js';

import {getTemplate} from './catsxp_rule_code_dialog.html.js'

const SettingsCatsxpRuleCodePageBase = PrefsMixin(I18nMixin(BaseMixin(PolymerElement)))

class SettingsCatsxpRuleCodePageElement extends
SettingsCatsxpRuleCodePageBase {
  static get is() {
    return 'settings-catsxp-rule-code-dialog'
  }

  static get template() {
    return getTemplate()
  }

  static get properties() {
    return {
      ruleCode: {
        type: String,
        notify: true
      },
      /**
       * 'qr' | 'words' | 'choose' | 'input'
       */
      codeType: {
        type: String,
        value: 'input',
        notify: true
      },
      dateType: {
        type: String,
        value: 'ads',
        notify: true
      },
      ruleCodeRowsCount_: {
        type: Number,
        computed: 'computeRuleCodeRowsCount_(ruleCode)'
      },
      hasCopiedRuleCode_: {
        type: Boolean,
        value: false
      },
    }
  }

  declare private ruleCode: string;
  declare private codeType: string;
  declare private dateType: string;
  declare private hasCopiedRuleCode_: boolean;
  declare private hasCopiedRuleCodeTimer_:number;

  computeRuleCodeRowsCount_() {
    if (!this.ruleCode) {
      return 0
    }
    return this.ruleCode.split(/[\n]/).length
  }

  isCodeType(askingType: string) {
    return (this.codeType === askingType)
  }

  handleClose_() {
    this.codeType = ''
  }

  handleRuleCodeCopy_() {
    window.clearTimeout(this.hasCopiedRuleCodeTimer_)
    navigator.clipboard.writeText(this.ruleCode)
    this.hasCopiedRuleCode_ = true
    this.hasCopiedRuleCodeTimer_ = window.setTimeout(() => {
      this.hasCopiedRuleCode_ = false
    }, 4000)
  }

  handleDone_() {
    this.fire('done')
  }

  shouldShowADSHelp_() {
    return this.dateType == 'ADS'
  }

  shouldShowCookiesHelp_() {
    return this.dateType == 'Cookies'
  }
}

customElements.define(
  SettingsCatsxpRuleCodePageElement.is, SettingsCatsxpRuleCodePageElement)
