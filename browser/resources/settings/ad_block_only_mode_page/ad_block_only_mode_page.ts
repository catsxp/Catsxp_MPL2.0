/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js'
import {PrefsMixin} from '/shared/settings/prefs/prefs_mixin.js'

import {getTemplate} from './ad_block_only_mode_page.html.js'

class CatsxpSettingsAdBlockOnlyModePage extends PrefsMixin(PolymerElement) {
  static get is() {
    return 'settings-ad-block-only-mode-page'
  }

  static get template() {
    return getTemplate()
  }
}

customElements.define(CatsxpSettingsAdBlockOnlyModePage.is,
                      CatsxpSettingsAdBlockOnlyModePage);
