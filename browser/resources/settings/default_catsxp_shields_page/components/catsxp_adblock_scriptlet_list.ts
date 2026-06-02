/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import 'chrome://resources/cr_elements/cr_button/cr_button.js'
import 'chrome://resources/cr_elements/icons.html.js'

import { PrefsMixin } from '/shared/settings/prefs/prefs_mixin.js'
import { I18nMixin } from 'chrome://resources/cr_elements/i18n_mixin.js'
import { PolymerElement } from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js'

import { BaseMixin } from '../../base_mixin.js'

import { getTemplate } from './catsxp_adblock_scriptlet_list.html.js'

import { loadTimeData } from '../../i18n_setup.js'

import {
  Scriptlet,
  CatsxpAdblockBrowserProxyImpl,
  ErrorCode
} from '../catsxp_adblock_browser_proxy.js'

import './catsxp_adblock_scriptlet_editor.js'

const AdblockScriptletListBase = PrefsMixin(
  I18nMixin(BaseMixin(PolymerElement))
)

class AdblockScriptletList extends AdblockScriptletListBase {
  static get is() {
    return 'adblock-scriptlet-list'
  }

  static get template() {
    return getTemplate()
  }

  static get properties() {
    return {
      customScriptletsList_: {
        type: Array
      },
      editingScriptlet_: Scriptlet,
      isEditing_: Boolean
    }
  }

  declare customScriptletsList_: Scriptlet[]
  declare editingScriptlet_: Scriptlet | null
  declare isEditing_: boolean

  browserProxy_ = CatsxpAdblockBrowserProxyImpl.getInstance()

  override ready() {
    super.ready()

    if (loadTimeData.getBoolean('shouldExposeElementsForTesting')) {
      (window as any).testing = (window as any).testing || {};
      (window as any).testing[`adblockScriptletList`] = this.shadowRoot;
    }

    this.isEditing_ = false
    this.browserProxy_.getCustomScriptlets().then((scriptlets) => {
      this.customScriptletsList_ = scriptlets
    })

    this.browserProxy_.addWebUiListener(
      'catsxp_adblock.onCustomResourcesChanged',
      () => {
        this.browserProxy_.getCustomScriptlets().then((value: Scriptlet[]) => {
          this.customScriptletsList_ = value
        })
      },
    )
  }

  handleAdd_(_: any) {
    this.editingScriptlet_ = new Scriptlet()
    this.isEditing_ = true
  }

  handleEdit_(e: any) {
    this.editingScriptlet_ = this.customScriptletsList_[e.model.index]
    this.isEditing_ = true
  }

  handleDelete_(e: any) {
    if (!loadTimeData.getBoolean('shouldExposeElementsForTesting')) {
      const messageText = this.i18n('adblockCustomScriptletDeleteConfirmation')
      if (!confirm(messageText)) {
        return
      }
    }

    this.browserProxy_.removeCustomScriptlet(
      this.customScriptletsList_[e.model.index].name,
    )
  }

  scriptletEditorClosed_(_: any) {
    this.editingScriptlet_ = null
    this.isEditing_ = false
  }
}

customElements.define(AdblockScriptletList.is, AdblockScriptletList)
