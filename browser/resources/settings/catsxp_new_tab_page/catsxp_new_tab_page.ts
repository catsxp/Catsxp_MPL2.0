/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import 'chrome://resources/polymer/v3_0/iron-collapse/iron-collapse.js';
import 'chrome://resources/polymer/v3_0/iron-icon/iron-icon.js';

import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';
import {I18nMixin, I18nMixinInterface} from 'chrome://resources/cr_elements/i18n_mixin.js'
import {WebUiListenerMixin, WebUiListenerMixinInterface} from 'chrome://resources/cr_elements/web_ui_listener_mixin.js';
import {BaseMixin} from '../base_mixin.js'
import {NewTabOption, CatsxpNewTabBrowserProxy, CatsxpNewTabBrowserProxyImpl} from './catsxp_new_tab_browser_proxy.js'
import {getTemplate} from './catsxp_new_tab_page.html.js'

/**
 * 'settings-catsxp-new-tab-page' is the settings page containing
 * catsxp's new tab features.
 */

const SettingsCatsxpNewTabPageElementBase =
  BaseMixin(WebUiListenerMixin(I18nMixin(PolymerElement))) as {
    new(): PolymerElement & WebUiListenerMixinInterface & I18nMixinInterface
  }

export class SettingsCatsxpNewTabPageElement extends SettingsCatsxpNewTabPageElementBase {
  static get is() {
    return 'settings-catsxp-new-tab-page'
  }

  static get template() {
    return getTemplate()
  }

  static get properties() {
    return {
      newTabShowOptions_: Array,
      showNewTabDashboardSettings_: Boolean,
    };
  }

  declare private newTabShowOptions_: NewTabOption[];
  declare private showNewTabDashboardSettings_: boolean;

  browserProxy_: CatsxpNewTabBrowserProxy = CatsxpNewTabBrowserProxyImpl.getInstance();

  override ready() {
    super.ready()
    this.openNewTabPage_ = this.openNewTabPage_.bind(this)

    this.browserProxy_.getNewTabShowsOptionsList().then((list: NewTabOption[]) => {
      this.newTabShowOptions_ = list
    })
    this.browserProxy_.shouldShowNewTabDashboardSettings().then((show: boolean) => {
      this.showNewTabDashboardSettings_ = show
    })
    this.addWebUiListener(
      'show-new-tab-dashboard-settings-changed', (show: boolean) => {
        this.showNewTabDashboardSettings_ = show
    })
  }

  openNewTabPage_() {
    window.open("chrome://newTab?openSettings=1", "_self")
  }
}

customElements.define(
  SettingsCatsxpNewTabPageElement.is, SettingsCatsxpNewTabPageElement)
