/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js'
import {AdBlockOnlyModeMixin} from './ad_block_only_mode_mixin.js'

import {getTemplate} from './ad_block_only_mode_alert.html.js'

class CatsxpSettingsAdBlockOnlyModeAlert extends AdBlockOnlyModeMixin(PolymerElement) {
  static get is() {
    return 'settings-ad-block-only-mode-alert'
  }

  static get template() {
    return getTemplate()
  }

  onTurnOffAdBlockOnlyMode_() {
    this.setAdBlockOnlyModeEnabled(false)
  }
}

customElements.define(CatsxpSettingsAdBlockOnlyModeAlert.is,
                      CatsxpSettingsAdBlockOnlyModeAlert);
