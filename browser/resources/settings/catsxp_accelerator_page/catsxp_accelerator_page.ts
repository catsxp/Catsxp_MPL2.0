/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import { WebUiListenerMixin, WebUiListenerMixinInterface } from 'chrome://resources/cr_elements/web_ui_listener_mixin.js';
import { PolymerElement } from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';

import { BaseMixin } from '../base_mixin.js'
import { loadTimeData } from '../i18n_setup.js'
import { Router} from '../router.js'

import {SettingsViewMixin} from '../settings_page/settings_view_mixin.js';

import { BossKeyBindingController } from './catsxp_boss_key_binding_controller.js';
import { getTemplate } from './catsxp_accelerator_page.html.js'
import '../shortcuts_page/shortcuts_page.js'

const SettingsCatsxpAcceleratorPageElementBase =
  WebUiListenerMixin(BaseMixin(SettingsViewMixin(PolymerElement)))

export class SettingsCatsxpAcceleratorPageElement extends
  SettingsCatsxpAcceleratorPageElementBase {

  static get is() {
    return 'settings-catsxp-accelerator-page'
  }

  static get template() {
    return getTemplate()
  }

  static get observers() {
    return [
      'bossKeyEnabledPrefChanged_(prefs.catsxp.accelerator.boss_key_enabled.value)',
      'bossKeyCommandTextPrefChanged_(prefs.catsxp.accelerator.boss_key_command_text.value)',
    ]
  }

  static get properties() {
    return {
      prefs: {
        type: Object,
        notify: true,
      },

      pageVisibility: Object,

      bossKeyBindingController_: Object,
    }
  }

  private bossKeyBindingController_: BossKeyBindingController;

  override ready() {
    super.ready()
    this.bossKeyBindingController_ = new BossKeyBindingController(this)
  }

  bossKeyEnabledPrefChanged_(value: any) {
    var node = this.root!.querySelector('#catsxp-boss-key-command-config-container') as HTMLElement
    node.hidden = !value;
  }

  bossKeyCommandTextPrefChanged_(value: any) {
    var node = this.root!.querySelector('#catsxp-boss-key-command-text') as HTMLElement
    node.textContent = value;
  }

  viewAllShortcutKeys_() {
    window.open("chrome://commands", "_blank")
  }

  onShortcutsClicked_() {
    const router = Router.getInstance();
    router.navigateTo(router.getRoutes().SHORTCUTS);
  }
}

customElements.define(
  SettingsCatsxpAcceleratorPageElement.is, SettingsCatsxpAcceleratorPageElement)
