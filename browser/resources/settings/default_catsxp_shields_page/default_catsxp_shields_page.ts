/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import './catsxp_adblock_subpage.js'
import './catsxp_rule_code_dialog.js'
import '//resources/cr_elements/md_select.css.js'

import { PolymerElement } from '//resources/polymer/v3_0/polymer/polymer_bundled.min.js'
import { PrefsMixin } from '/shared/settings/prefs/prefs_mixin.js'
import { I18nMixin } from 'chrome://resources/cr_elements/i18n_mixin.js'
import { WebUiListenerMixin } from 'chrome://resources/cr_elements/web_ui_listener_mixin.js'
import {AdBlockOnlyModeMixin} from '../ad_block_only_mode_page/ad_block_only_mode_mixin.js'

import { loadTimeData } from '../i18n_setup.js'
import { Router } from '../router.js'
import { SettingsToggleButtonElement } from '../controls/settings_toggle_button.js'

import { SettingsViewMixin } from '../settings_page/settings_view_mixin.js';

import {
  DefaultCatsxpShieldsBrowserProxy,
  DefaultCatsxpShieldsBrowserProxyImpl
} from './default_catsxp_shields_browser_proxy.js'

import { getTemplate } from './default_catsxp_shields_page.html.js'

import '../ad_block_only_mode_page/ad_block_only_mode_alert.js'
import '../social_blocking_page/social_blocking_page.js';

interface CatsxpShieldsPage {
  $: {
    adControlType: HTMLSelectElement,
    cookieControlType: HTMLSelectElement,
    fingerprintingToggleControlType: SettingsToggleButtonElement,
    fingerprintingSelectControlType: HTMLSelectElement,
    forgetFirstPartyStorageControlType: SettingsToggleButtonElement,
    httpsUpgradeControlType: HTMLSelectElement,
    noScriptControlToggle: SettingsToggleButtonElement,
    setContactInfoSaveFlagToggle: SettingsToggleButtonElement,
    allowElementBlockerInPrivateModeToggle: SettingsToggleButtonElement,
  }
}

type ControlType = {
  name: string
  value: string
}

const CatsxpShieldsPageBase =
  AdBlockOnlyModeMixin(WebUiListenerMixin(I18nMixin(PrefsMixin(SettingsViewMixin(PolymerElement)))))

/**
 * 'settings-default-catsxp-shields-page' is the settings page containing catsxp's
 * default shields.
 */
class CatsxpShieldsPage extends CatsxpShieldsPageBase {
  static get is() {
    return 'settings-default-catsxp-shields-page'
  }

  static get template() {
    return getTemplate()
  }

  static get properties() {
    return {
      adControlTypes_: {
        readOnly: true,
        type: Array,
        value: function () {
          return [
            { value: 'block', name: loadTimeData.getString('blockAdsTrackersAggressive') },
            { value: 'block_third_party', name: loadTimeData.getString('blockAdsTrackersStandard') },
            { value: 'allow', name: loadTimeData.getString('allowAdsTrackers') }
          ]
        }
      },
      fingerprintingControlTypes_: {
        readOnly: true,
        type: Array,
        value: function () {
          return [
            { value: 'block', name: loadTimeData.getString('strictFingerprinting') },
            { value: 'default', name: loadTimeData.getString('standardFingerprinting') },
            { value: 'allow', name: loadTimeData.getString('allowAllFingerprinting') }
          ]
        }
      },
      httpsUpgradeControlTypes_: {
        readOnly: true,
        type: Array,
        value: function () {
          return [
            {
              value: 'block',
              name: loadTimeData.getString('strictHttpsUpgrade')
            },
            {
              value: 'block_third_party',
              name: loadTimeData.getString('standardHttpsUpgrade')
            },
            {
              value: 'allow',
              name: loadTimeData.getString('disabledHttpsUpgrade')
            }
          ]
        }
      },
      adControlType_: String,
      cookieControlTypes_: Array,
      cookieControlType_: {
        type: String,
        value: 'block_third_party'
      },
      fingerprintingControlType_: String,
      httpsUpgradeControlType_: String,
      isAdBlockRoute_: {
        type: Boolean,
        value: false
      },
      isDebounceFeatureEnabled_: {
        readOnly: true,
        type: Boolean,
        value: function () {
          return loadTimeData.getBoolean('isDebounceFeatureEnabled')
        }
      },
      isShowCatsxpShieldsInPageInfoEnabled_: {
        type: Boolean,
        value: loadTimeData.getBoolean('isShowCatsxpShieldsInPageInfoEnabled')
      },
      isHttpsByDefaultEnabled_: {
        type: Boolean,
        value: loadTimeData.getBoolean('isHttpsByDefaultEnabled')
      },
      showStrictFingerprintingMode_: {
        type: Boolean,
        value: loadTimeData.getBoolean('showStrictFingerprintingMode')
      },
      isForgetFirstPartyStorageFeatureEnabled_: {
        type: Boolean,
        value: loadTimeData.getBoolean('isForgetFirstPartyStorageFeatureEnabled')
      },
      noScriptControlType_: {
        type: Object,
        value: {
          key: '',
          type: chrome.settingsPrivate.PrefType.BOOLEAN,
          value: false,
        }
      },
      isForgetFirstPartyStorageEnabled_: {
        type: Object,
        value: {
          key: '',
          type: chrome.settingsPrivate.PrefType.BOOLEAN,
          value: false,
        }
      },
      isFingerprintingEnabled_: {
        type: Object,
        value: {
          key: '',
          type: chrome.settingsPrivate.PrefType.BOOLEAN,
          value: true,
        }
      },
      isContactInfoSaveFlagEnabled_: {
        type: Object,
        value: {
          key: '',
          type: chrome.settingsPrivate.PrefType.BOOLEAN,
          value: true,
        }
      },
      isBlockElementFeatureEnabled_: {
        type: Boolean,
        value: loadTimeData.getBoolean('isBlockElementFeatureEnabled')
      },
      isAllowElementBlockerInPrivateModeEnabled_: {
        type: Object,
        value: {
          key: '',
          type: chrome.settingsPrivate.PrefType.BOOLEAN,
          value: true,
        }
      },
      ruleCode_: {
        type: String,
        notify: true
      },
      isInvalidRuleCode_: {
        type: Boolean,
        value: false,
      },
      onManageADSRulePack_: {
        type: Boolean,
        value: false
      },
      onManageRule_: {
        type: Boolean,
        value: false
      },
      cookieControlEnabled_: {
        type: Boolean,
        value: true
      },
      ruleCodeDialogType_: String,
      ruleCodeDialogDate_: String,
    }
  }

  private declare adControlTypes_: ControlType[]
  private declare adControlType_: 'allow' | 'block' | 'block_third_party'
  private declare isAdBlockRoute_: boolean
  private declare cookieControlTypes_: ControlType[]
  private declare cookieControlType_: string
  private declare httpsUpgradeControlType_: string
  private declare noScriptControlType_: chrome.settingsPrivate.PrefObject<boolean>
  private declare isForgetFirstPartyStorageEnabled_: chrome.settingsPrivate.
    PrefObject<boolean>
  private declare isFingerprintingEnabled_: chrome.settingsPrivate.PrefObject<boolean>
  private declare isContactInfoSaveFlagEnabled_: chrome.settingsPrivate.
    PrefObject<boolean>
  private declare isAllowElementBlockerInPrivateModeEnabled_: chrome.
    settingsPrivate.PrefObject<boolean>
  private declare fingerprintingControlTypes_: ControlType[]
  private declare fingerprintingControlType_: string
  private declare httpsUpgradeControlTypes_: ControlType[]
  private declare isHttpsByDefaultEnabled_: boolean
  private declare isShowCatsxpShieldsInPageInfoEnabled_: boolean
  private declare showStrictFingerprintingMode_: boolean
  private declare isBlockElementFeatureEnabled_: boolean
  private declare isForgetFirstPartyStorageFeatureEnabled_: boolean
  private declare ruleCode_:string
  private declare isInvalidRuleCode_:boolean
  private declare onManageADSRulePack_:boolean
  private declare onManageRule_:boolean
  private declare cookieControlEnabled_:boolean
  private declare ruleCodeDialogType_: string
  private declare ruleCodeDialogDate_: string


  private browserProxy_: DefaultCatsxpShieldsBrowserProxy =
    DefaultCatsxpShieldsBrowserProxyImpl.getInstance()

  override ready () {
    super.ready()

    this.onShieldsSettingsChanged_()

    this.addWebUiListener('catsxp-shields-settings-changed',
      () => { this.onShieldsSettingsChanged_() })
  }

  override getAssociatedControlFor(childViewId: string): HTMLElement {
    switch (childViewId) {
      case 'adblock':
        return this.shadowRoot!.querySelector('#contentFiltersRow')!;
      default:
        throw new Error(`Unknown child view id: ${childViewId}`)
    }
  }

  onAdblockPageClick_() {
    const router = Router.getInstance()
    router.navigateTo(router.getRoutes().SHIELDS_ADBLOCK)
  }

  controlEqual_ (val1: any, val2: any) {
    return val1 === val2
  }

  onShieldsSettingsChanged_() {
    Promise.all([this.browserProxy_.isAdControlEnabled(), this.browserProxy_.isFirstPartyCosmeticFilteringEnabled()])
      .then(([adControlEnabled, hide1pContent]) => {
        // When Adblock Only Mode is enabled, set ad control type to 'allow'
        // (shown as Disabled in UI) based on spec and Figma design.
        if (adControlEnabled && !this.isAdBlockOnlyModeEnabled_) {
          this.adControlType_ = hide1pContent ? 'block' : 'block_third_party'
        } else {
          this.adControlType_ = 'allow'
        }
      })

    this.browserProxy_.getCookieControlType().then(value => {
      this.cookieControlType_ = value;
      this.cookieControlEnabled_ = (this.cookieControlType_ !== 'allow')
    })

    this.browserProxy_.getFingerprintingControlType().then(value => {
      this.fingerprintingControlType_ = value
      this.isFingerprintingEnabled_ = {
        key: '',
        type: chrome.settingsPrivate.PrefType.BOOLEAN,
        value: value !== 'allow',
      }
    })

    this.browserProxy_.getHttpsUpgradeControlType().then(value => {
      this.httpsUpgradeControlType_ = value
    })

    this.browserProxy_.getNoScriptControlType().then(value => {
      this.noScriptControlType_ = {
        key: '',
        type: chrome.settingsPrivate.PrefType.BOOLEAN,
        value: value,
      }
    })

    this.browserProxy_.getHideBlockAllCookieTogle().then(value => {
      this.cookieControlTypes_ = [
        {
          value: 'block_third_party',
          name: loadTimeData.getString('block3rdPartyCookies')
        },
        {
          value: 'allow',
          name: loadTimeData.getString('allowAllCookies')
        }
      ]
      if (!value) {
        this.cookieControlTypes_.unshift({
          value: 'block',
          name: loadTimeData.getString('blockAllCookies')
        })
      }
    })

    this.browserProxy_.getForgetFirstPartyStorageEnabled().then(value => {
      this.isForgetFirstPartyStorageEnabled_ = {
        key: '',
        type: chrome.settingsPrivate.PrefType.BOOLEAN,
        value: value,
      }
    })
    this.browserProxy_.getContactInfo().then(value => {
      this.isContactInfoSaveFlagEnabled_ = {
        key: '',
        type: chrome.settingsPrivate.PrefType.BOOLEAN,
        value: value.contactInfoSaveFlag,
      }
    })

    this.browserProxy_.getAllowElementBlockerInPrivateModeEnabled()
      .then(value => {
        this.isAllowElementBlockerInPrivateModeEnabled_ = {
          key: '',
          type: chrome.settingsPrivate.PrefType.BOOLEAN,
          value: value,
        }
    })
  }

  onAdControlChange_() {
    const setting = this.$.adControlType.value
    const adControlType = (setting !== 'allow')
    this.browserProxy_.setAdControlType(adControlType)
    this.browserProxy_.setCosmeticFilteringControlType(setting)
  }

  onCookieControlChange_() {
    const setting = this.$.cookieControlType.value
    this.cookieControlEnabled_ = (setting !== 'allow')
    this.browserProxy_.setCookieControlType(setting)
  }

  onFingerprintingSelectControlChange_() {
    this.browserProxy_.setFingerprintingControlType(this.$.fingerprintingSelectControlType.value)
  }

  onFingerprintingToggleControlChange_() {
    this.browserProxy_.setFingerprintingBlockEnabled(this.$.fingerprintingToggleControlType.checked)
  }

  onHttpsUpgradeControlChange_() {
    console.log(this.$.httpsUpgradeControlType.value)
    this.browserProxy_.setHttpsUpgradeControlType(
      this.$.httpsUpgradeControlType.value)
  }

  onNoScriptControlChange_() {
    this.browserProxy_.
      setNoScriptControlType(this.$.noScriptControlToggle.checked)
  }

  onForgetFirstPartyStorageToggleChange_() {
    this.browserProxy_.setForgetFirstPartyStorageEnabled(
      this.$.forgetFirstPartyStorageControlType.checked
    )
  }

  onAllowElementBlockerInPrivateModeToggle_ () {
    this.browserProxy_.setAllowElementBlockerInPrivateModeEnabled(
      this.$.allowElementBlockerInPrivateModeToggle.checked
    )
  }

  onSaveContactInfoToggle_() {
    this.browserProxy_.setContactInfoSaveFlag(
      this.$.setContactInfoSaveFlagToggle.checked
    )
  }

  handleRuleCodeDialogDone_() {
    this.submitRuleCode_(this.ruleCodeDialogDate_)
  }

  async submitRuleCode_(ruleType: string) {
    const ruleCodeToSubmit = this.ruleCode_ || ''
    let success = false
    try {
      success = await this.browserProxy_.setCustomRule(ruleType, ruleCodeToSubmit)
    } catch (e) {
      console.error("Error setting rule code")
      success = false
    }
    if (!success) {
      this.isInvalidRuleCode_ = true
    } else {
      this.isInvalidRuleCode_ = false
      this.ruleCodeDialogType_ = ''
    }
  }

  async manageCustomCookiesRule_() {
    await this.ensureSetCustomCookiesRule_()
    this.ruleCodeDialogType_ = 'input'
    this.ruleCodeDialogDate_ = 'Cookies'
  }

  async ensureSetCustomCookiesRule_() {
    const ruleCode = await this.browserProxy_.getCustomRule('Cookies')
    this.ruleCode_ = ruleCode
  }

  restartBrowser_(e: Event) {
    e.stopPropagation()
    window.open("chrome://restart", "_self")
  }

  shouldShowRestart_(val1: boolean) {
    if (loadTimeData.getBoolean('closeShieldManager') != val1)
      return true
    return false
  }

  manageADSRuleUrl_() {
    window.open("chrome://adblock/", "_self")
  }

  shouldManager_(value: number) {
    return value == 1
  }
}

customElements.define(
  CatsxpShieldsPage.is, CatsxpShieldsPage)
