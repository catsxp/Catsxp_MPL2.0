/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

import 'chrome://resources/cr_elements/cr_dialog/cr_dialog.js';
import 'chrome://resources/cr_elements/icons.html.js';
import '../settings_page/settings_subpage.js';
import '../settings_shared.css.js';
import '../settings_vars.css.js';
import './catsxp_sync_subpage.js';
import './catsxp_sync_manage_devices_page.js';
import type {CrViewManagerElement} from 'chrome://resources/cr_elements/cr_view_manager/cr_view_manager.js';

import {SyncBrowserProxy, SyncBrowserProxyImpl, SyncPrefs} from '/shared/settings/people_page/sync_browser_proxy.js';
import {I18nMixin, I18nMixinInterface} from 'chrome://resources/cr_elements/i18n_mixin.js'
import {WebUiListenerMixin, WebUiListenerMixinInterface} from 'chrome://resources/cr_elements/web_ui_listener_mixin.js';
import {PolymerElement} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';

import {BaseMixin} from '../base_mixin.js'
import {Route, Router} from '../router.js';
import {routes} from '../route.js';
import {RouteObserverMixin, RouteObserverMixinInterface} from '../router.js';
import type {SettingsPlugin} from '../settings_main/settings_plugin.js';
import {SearchableViewContainerMixin, SearchableViewContainerMixinInterface} from '../settings_page/searchable_view_container_mixin.js';


import {CatsxpSyncBrowserProxy, CatsxpSyncStatus} from './catsxp_sync_browser_proxy.js';
import {getTemplate} from './catsxp_sync_page_index.html.js'

/**
 * @fileoverview
 * 'settings-catsxp-sync-page-index' is the settings page containing catsxp's
 * custom sync.
 */

const SettingsCatsxpSyncPageElementBase =
SearchableViewContainerMixin(RouteObserverMixin(I18nMixin(WebUiListenerMixin(BaseMixin(PolymerElement))))) as {
    new(): PolymerElement
      & WebUiListenerMixinInterface
      & I18nMixinInterface
      & RouteObserverMixinInterface
      & SearchableViewContainerMixinInterface
  }

export interface SettingsCatsxpSyncPageElement {
  $: {
    viewManager: CrViewManagerElement,
  };
}

export class SettingsCatsxpSyncPageElement extends SettingsCatsxpSyncPageElementBase implements SettingsPlugin {
  static get is() {
    return 'settings-catsxp-sync-page-index'
  }

  static get template() {
    return getTemplate()
  }

  static get properties() {
    return {
      prefs: Object,
      /**
       * The current sync status, supplied by SyncBrowserProxy.
       * @type {?SyncStatus}
       */
      syncStatus_: Object,
      isEncryptionSet_: {
        type: Boolean,
        value: false
      },
      syncLabel_: {
        type: String,
        computed: 'computeSyncLabel_(syncStatus_)'
      },
    };
  }

  declare prefs: {[key: string]: any};

  private declare syncStatus_: CatsxpSyncStatus;
  private declare isEncryptionSet_: boolean;
  private declare syncLabel_: string;

  browserProxy_: SyncBrowserProxy = SyncBrowserProxyImpl.getInstance();
  catsxpBrowserProxy_: CatsxpSyncBrowserProxy = CatsxpSyncBrowserProxy.getInstance();

  computeSyncLabel_() {
    if (this.syncStatus_ !== undefined &&
        this.syncStatus_.hasSyncWordsDecryptionError) {
        return this.i18n('catsxpSyncCouldNotSyncActionLabel');
    }
    const isAlreadySetup = this.syncStatus_ !== undefined &&
        !this.syncStatus_.firstSetupInProgress;
    const key = isAlreadySetup ? 'catsxpSyncManageActionLabel' : 'catsxpSyncSetupActionLabel';
    return this.i18n(key);
  }

  override connectedCallback() {
    super.connectedCallback()
    const onSyncStatus = this.handleSyncStatus_.bind(this)
    this.catsxpBrowserProxy_.getSyncStatus().then(
        (status: CatsxpSyncStatus) => onSyncStatus(status));
    this.addWebUiListener(
      'sync-prefs-changed', this.handleSyncPrefsChanged_.bind(this));
    this.addWebUiListener('sync-status-changed', onSyncStatus);
  }

  /**
   * Handler for when the sync state is pushed from the browser.
   */
  handleSyncStatus_(syncStatus: CatsxpSyncStatus) {
    this.syncStatus_ = syncStatus;
  }

  /**
   * Handler for when the sync preferences are updated.
   */
  async handleSyncPrefsChanged_(syncPrefs: SyncPrefs) {
    if (this.syncStatus_ && !this.syncStatus_.firstSetupInProgress) {
      const pureSyncCode = await this.catsxpBrowserProxy_.getPureSyncCode()
      if (syncPrefs.passphraseRequired) {
        await this.browserProxy_.setDecryptionPassphrase(pureSyncCode);
      } else if (!this.isEncryptionSet_) {
        this.browserProxy_.setEncryptionPassphrase(pureSyncCode)
        .then(successfullySet => {
          this.isEncryptionSet_ = successfullySet
        })
      }
    }
  }

  override currentRouteChanged(newRoute: Route, oldRoute?: Route) {
    super.currentRouteChanged(newRoute, oldRoute);

    // Need to wait for currentRouteChanged observers on child views to run
    // first, before switching views.
    queueMicrotask(() => {
      switch (newRoute) {
        case routes.CATSXP_SYNC:
        case routes.BASIC:
          this.$.viewManager.switchView(
              'catsxpSync', 'no-animation', 'no-animation');
          break;
        case routes.CATSXP_SYNC_SETUP:
          this.$.viewManager.switchView(
              'setup', 'no-animation', 'no-animation');
          break;
      }
    });
  }
}

customElements.define(
  SettingsCatsxpSyncPageElement.is, SettingsCatsxpSyncPageElement)
