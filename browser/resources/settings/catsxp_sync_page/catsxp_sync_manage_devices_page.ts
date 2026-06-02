/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import '../settings_shared.css.js';
import '../settings_vars.css.js';

import { I18nMixin, I18nMixinInterface } from 'chrome://resources/cr_elements/i18n_mixin.js'
import { PolymerElement } from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';

import { BaseMixin } from '../base_mixin.js'
import { Route, Router } from '../router.js';
import { SettingsViewMixin, SettingsViewMixinInterface } from '../settings_page/settings_view_mixin.js';


import { getTemplate } from './catsxp_sync_manage_devices_page.html.js'

const SettingsCatsxpSyncManageDevicesPageElementBase =
  SettingsViewMixin(I18nMixin(BaseMixin(PolymerElement))) as {
    new(): PolymerElement
      & I18nMixinInterface
      & SettingsViewMixinInterface
  }

export class SettingsCatsxpSyncManageDevicesPageElement extends SettingsCatsxpSyncManageDevicesPageElementBase {
  static get is() {
    return 'settings-catsxp-sync-manage-devices-page'
  }

  static get template() {
    return getTemplate()
  }

  static get properties() {
    return {
      label: {
        type: String,
      },
    };
  }

  declare label: string;

  onSyncTap_() {
    // Users can go to sync subpage regardless of sync status.
    const router = Router.getInstance();
    router.navigateTo(
      (router.getRoutes() as { CATSXP_SYNC_SETUP: Route }).CATSXP_SYNC_SETUP);
  }

  override getAssociatedControlFor(childViewId: string): HTMLElement {
    switch (childViewId) {
      case 'setup':
        return this.shadowRoot!.querySelector('#catsxp-sync-setup')!;
      default:
        throw new Error(`Unknown child view id: ${childViewId}`)
    }
  }
}

customElements.define(
  SettingsCatsxpSyncManageDevicesPageElement.is, SettingsCatsxpSyncManageDevicesPageElement)

