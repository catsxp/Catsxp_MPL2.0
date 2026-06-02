/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import 'chrome://resources/cr_elements/cr_icon_button/cr_icon_button.js'
import 'chrome://resources/cr_elements/icons.html.js'

import {PrefsMixin} from '/shared/settings/prefs/prefs_mixin.js'
import {I18nMixin} from 'chrome://resources/cr_elements/i18n_mixin.js'
import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js'

import {BaseMixin} from '../../base_mixin.js'

import {getTemplate} from './catsxp_adblock_subscribe_dropdown.html.js'

import type {
  CrActionMenuElement
} from 'chrome://resources/cr_elements/cr_action_menu/cr_action_menu.js'

interface AdBlockSubscribeDropDown {
  $: {
    menu: CrActionMenuElement
  }
}

const AdblockSubscribeDropDownBase =
  PrefsMixin(I18nMixin(BaseMixin(PolymerElement)))

class AdBlockSubscribeDropDown extends AdblockSubscribeDropDownBase {
  static get is() {
    return 'adblock-subscribe-dropdown'
  }

  static get template() {
    return getTemplate()
  }

  handleDropdownClick_(e: Event) {
    this.$.menu.showAt(e.target as HTMLElement)
  }

  updateSubscription_() {
    this.fire('update-subscription')
    this.$.menu.close()
  }

  viewSubscription_() {
    this.fire('view-subscription')
    this.$.menu.close()
  }

  deleteSubscription_() {
    this.fire('delete-subscription')
    this.$.menu.close()
  }
}

customElements.define(AdBlockSubscribeDropDown.is, AdBlockSubscribeDropDown)
