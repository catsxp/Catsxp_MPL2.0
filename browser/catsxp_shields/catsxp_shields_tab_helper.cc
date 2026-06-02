/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_shields/catsxp_shields_tab_helper.h"

#include <string>
#include <utility>

#include "base/check_deref.h"
#include "base/i18n/number_formatting.h"
#include "base/metrics/histogram_macros.h"
#include "base/notreached.h"
#include "base/strings/utf_string_conversions.h"
#include "catsxp/browser/catsxp_shields/catsxp_shields_settings_service_factory.h"
#include "catsxp/browser/catsxp_shields/catsxp_shields_web_contents_observer.h"
#include "catsxp/browser/ephemeral_storage/ephemeral_storage_service_factory.h"
#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_locale_utils.h"
#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_settings_service.h"
#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_utils.h"
#include "catsxp/components/catsxp_shields/core/common/catsxp_shield_constants.h"
#include "catsxp/components/catsxp_shields/core/common/features.h"
#include "catsxp/components/catsxp_shields/core/common/pref_names.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/cookie_settings_factory.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "components/content_settings/core/browser/cookie_settings.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "components/favicon/content/content_favicon_driver.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/reload_type.h"
#include "content/public/browser/security_principal.h"
#include "content/public/browser/web_contents.h"
#include "net/base/features.h"
#include "net/base/url_util.h"

using net::AppendQueryParameter;

namespace {

constexpr char kShieldsAllowScriptOnceHistogramName[] =
    "Catsxp.Shields.AllowScriptOnce";

}  // namespace

bool IsAdBlockOnlyModeSupportedAndFeatureEnabled() {
  return base::FeatureList::IsEnabled(
             catsxp_shields::features::kAdblockOnlyMode) &&
         catsxp_shields::IsAdblockOnlyModeSupportedForLocale(
             g_browser_process->GetApplicationLocale());
}

namespace catsxp_shields {

CatsxpShieldsTabHelper::~CatsxpShieldsTabHelper() = default;

CatsxpShieldsTabHelper::CatsxpShieldsTabHelper(content::WebContents* web_contents)
    : content::WebContentsObserver(web_contents),
      content::WebContentsUserData<CatsxpShieldsTabHelper>(*web_contents),
      host_content_settings_map_(
          CHECK_DEREF(HostContentSettingsMapFactory::GetForProfile(
              web_contents->GetBrowserContext()))),
      catsxp_shields_settings_(
          CHECK_DEREF(CatsxpShieldsSettingsServiceFactory::GetForProfile(
              Profile::FromBrowserContext(web_contents->GetBrowserContext())))),
      ephemeral_storage_service_(EphemeralStorageServiceFactory::GetForContext(
          web_contents->GetBrowserContext())) {
  favicon::ContentFaviconDriver::FromWebContents(web_contents)
      ->AddObserver(this);
  observation_.Observe(&*host_content_settings_map_);
  local_state_change_registrar_.Init(g_browser_process->local_state());
  local_state_change_registrar_.Add(
      catsxp_shields::prefs::kAdBlockOnlyModeEnabled,
      base::BindRepeating(
          &CatsxpShieldsTabHelper::OnShieldsAdBlockOnlyModeEnabledChanged,
          base::Unretained(this)));
}

void CatsxpShieldsTabHelper::DidFinishNavigation(
    content::NavigationHandle* navigation_handle) {
  if (navigation_handle->IsInMainFrame() && navigation_handle->HasCommitted() &&
      !navigation_handle->IsSameDocument()) {
    if (navigation_handle->GetReloadType() != content::ReloadType::NORMAL) {
      // We are navigating to a new page or force-reloading. Therefore, clear
      // the webcompat features listed.
      webcompat_features_invoked_.clear();
    }
    ClearAllResourcesList();

    if (!navigation_triggered_by_shields_changes_) {
      MaybeNotifyRepeatedReloads(navigation_handle);
    }

    navigation_triggered_by_shields_changes_ = false;
  }
}

void CatsxpShieldsTabHelper::MaybeNotifyRepeatedReloads(
    content::NavigationHandle* navigation_handle) {
  if (!IsAdBlockOnlyModeSupportedAndFeatureEnabled() ||
      g_browser_process->local_state()->GetBoolean(
          catsxp_shields::prefs::kAdBlockOnlyModeEnabled)) {
    // Do not notify if ad block only mode feature is disabled or shields ad
    // block only mode is already enabled.
    return;
  }

  const PrefService* prefs =
      Profile::FromBrowserContext(web_contents()->GetBrowserContext())
          ->GetPrefs();
  if (prefs->GetBoolean(
          catsxp_shields::prefs::kAdBlockOnlyModePromptDismissed)) {
    // Do not notify if the prompt has been dismissed.
    return;
  }

  if (navigation_handle->GetRestoreType() == content::RestoreType::kRestored) {
    // Do not notify if the navigation is a restore.
    return;
  }

  if (!PageTransitionCoreTypeIs(navigation_handle->GetPageTransition(),
                                ui::PAGE_TRANSITION_RELOAD)) {
    // Do not notify if the navigation is not a reload.
    return;
  }

  const base::Time current_time = base::Time::Now();
  if (!repeated_reloads_counter_ ||
      current_time - repeated_reloads_counter_->initial_reload_at >
          features::kAdblockOnlyModePromptAfterPageReloadsInterval.Get()) {
    repeated_reloads_counter_ = RepeatedReloadsCounter{
        .initial_reload_at = current_time,
        .reloads_count = 0,
    };
  }

  // If the page is reloaded between `kAdblockOnlyModePromptAfterPageReloadsMin`
  // and `kAdblockOnlyModePromptAfterPageReloadsMax` times in
  // `kAdblockOnlyModePromptAfterPageReloadsInterval`, notify observers.
  repeated_reloads_counter_->reloads_count++;
  if (repeated_reloads_counter_->reloads_count >=
          features::kAdblockOnlyModePromptAfterPageReloadsMin.Get() &&
      repeated_reloads_counter_->reloads_count <=
          features::kAdblockOnlyModePromptAfterPageReloadsMax.Get()) {
    for (Observer& observer : observer_list_) {
      observer.OnRepeatedReloadsDetected();
    }
  }
}

void CatsxpShieldsTabHelper::OnShieldsAdBlockOnlyModeEnabledChanged() {
  for (Observer& observer : observer_list_) {
    observer.OnShieldsAdBlockOnlyModeEnabledChanged();
  }
}

void CatsxpShieldsTabHelper::WebContentsDestroyed() {
  favicon::ContentFaviconDriver::FromWebContents(web_contents())
      ->RemoveObserver(this);
  observation_.Reset();
}

void CatsxpShieldsTabHelper::OnContentSettingChanged(
    const ContentSettingsPattern& primary_pattern,
    const ContentSettingsPattern& secondary_pattern,
    ContentSettingsTypeSet content_type_set) {
  if ((content_type_set.ContainsAllTypes() ||
       content_type_set.GetType() == ContentSettingsType::CATSXP_SHIELDS) &&
      primary_pattern.Matches(GetCurrentSiteURL())) {
    for (Observer& obs : observer_list_) {
      obs.OnShieldsEnabledChanged();
    }
  }
}

void CatsxpShieldsTabHelper::OnFaviconUpdated(
    favicon::FaviconDriver* favicon_driver,
    NotificationIconType notification_icon_type,
    const GURL& icon_url,
    bool icon_url_changed,
    const gfx::Image& image) {
  for (Observer& obs : observer_list_) {
    obs.OnFaviconUpdated();
  }
}

void CatsxpShieldsTabHelper::ReloadWebContents() {
  navigation_triggered_by_shields_changes_ = true;

  web_contents()->GetController().Reload(content::ReloadType::NORMAL, true);
}

void CatsxpShieldsTabHelper::ClearAllResourcesList() {
  resource_list_blocked_ads_.clear();
  resource_list_http_redirects_.clear();
  resource_list_blocked_js_.clear();
  resource_list_blocked_fingerprints_.clear();
  resource_list_allowed_once_js_.clear();

  for (Observer& obs : observer_list_) {
    obs.OnResourcesChanged();
  }
}

void CatsxpShieldsTabHelper::AddObserver(Observer* obs) {
  observer_list_.AddObserver(obs);
}

void CatsxpShieldsTabHelper::RemoveObserver(Observer* obs) {
  observer_list_.RemoveObserver(obs);
}

bool CatsxpShieldsTabHelper::HasObserver(Observer* observer) {
  return observer_list_.HasObserver(observer);
}

int CatsxpShieldsTabHelper::GetTotalBlockedCount() {
  return (resource_list_blocked_ads_.size() +
          resource_list_http_redirects_.size() +
          resource_list_blocked_js_.size() +
          resource_list_blocked_fingerprints_.size());
}

std::vector<GURL> CatsxpShieldsTabHelper::GetBlockedAdsList() {
  std::vector<GURL> blocked_ads(resource_list_blocked_ads_.begin(),
                                resource_list_blocked_ads_.end());

  return blocked_ads;
}

std::vector<GURL> CatsxpShieldsTabHelper::GetHttpRedirectsList() {
  std::vector<GURL> http_redirects(resource_list_http_redirects_.begin(),
                                   resource_list_http_redirects_.end());

  return http_redirects;
}

std::vector<GURL> CatsxpShieldsTabHelper::GetBlockedJsList() {
  std::vector<GURL> js_list(resource_list_blocked_js_.begin(),
                            resource_list_blocked_js_.end());
  return js_list;
}

std::vector<GURL> CatsxpShieldsTabHelper::GetAllowedJsList() {
  std::vector<GURL> js_list(resource_list_allowed_once_js_.begin(),
                            resource_list_allowed_once_js_.end());
  return js_list;
}

std::vector<GURL> CatsxpShieldsTabHelper::GetFingerprintsList() {
  std::vector<GURL> fingerprints_list(
      resource_list_blocked_fingerprints_.begin(),
      resource_list_blocked_fingerprints_.end());

  return fingerprints_list;
}

const base::flat_set<ContentSettingsType>&
CatsxpShieldsTabHelper::GetInvokedWebcompatFeatures() {
  return webcompat_features_invoked_;
}

bool CatsxpShieldsTabHelper::GetCatsxpShieldsEnabled() {
  return catsxp_shields_settings_->GetCatsxpShieldsEnabled(GetCurrentSiteURL());
}

bool CatsxpShieldsTabHelper::GetAllowElementBlockerInPrivateModeEnabled() {
  return catsxp_shields::GetAllowElementBlockerInPrivateModeEnabled(
      g_browser_process->local_state());
}

void CatsxpShieldsTabHelper::SetCatsxpShieldsEnabled(bool is_enabled) {
  catsxp_shields_settings_->SetCatsxpShieldsEnabled(is_enabled,
                                                  GetCurrentSiteURL());

  if (IsAdBlockOnlyModeSupportedAndFeatureEnabled() && !is_enabled) {
    PrefService* prefs =
        Profile::FromBrowserContext(web_contents()->GetBrowserContext())
            ->GetPrefs();
    prefs->SetInteger(
        catsxp_shields::prefs::kShieldsDisabledCount,
        prefs->GetInteger(catsxp_shields::prefs::kShieldsDisabledCount) + 1);
  }

  ReloadWebContents();
}

bool CatsxpShieldsTabHelper::IsCatsxpShieldsAdBlockOnlyModeEnabled() {
  return IsAdBlockOnlyModeSupportedAndFeatureEnabled() &&
         g_browser_process->local_state()->GetBoolean(
             catsxp_shields::prefs::kAdBlockOnlyModeEnabled);
}

void CatsxpShieldsTabHelper::SetCatsxpShieldsAdBlockOnlyModeEnabled(
    bool is_enabled) {
  g_browser_process->local_state()->SetBoolean(
      catsxp_shields::prefs::kAdBlockOnlyModeEnabled, is_enabled);
  ReloadWebContents();
}

bool CatsxpShieldsTabHelper::ShouldShowShieldsDisabledAdBlockOnlyModePrompt() {
  PrefService* prefs =
      Profile::FromBrowserContext(web_contents()->GetBrowserContext())
          ->GetPrefs();
  return IsAdBlockOnlyModeSupportedAndFeatureEnabled() &&
         !prefs->GetBoolean(
             catsxp_shields::prefs::kAdBlockOnlyModePromptDismissed) &&
         prefs->GetInteger(catsxp_shields::prefs::kShieldsDisabledCount) >=
             features::kAdblockOnlyModePromptAfterShieldsDisabledCount.Get();
}

void CatsxpShieldsTabHelper::SetCatsxpShieldsAdBlockOnlyModePromptDismissed() {
  PrefService* prefs =
      Profile::FromBrowserContext(web_contents()->GetBrowserContext())
          ->GetPrefs();
  prefs->SetBoolean(catsxp_shields::prefs::kAdBlockOnlyModePromptDismissed,
                    true);
}

GURL CatsxpShieldsTabHelper::GetCurrentSiteURL() const {
  return web_contents()->GetLastCommittedURL();
}

GURL CatsxpShieldsTabHelper::GetFaviconURL(bool refresh) {
  auto url = GURL("chrome://favicon2/");
  url = AppendQueryParameter(url, "size", "16");
  url = AppendQueryParameter(url, "scaleFactor", "2x");
  url = AppendQueryParameter(url, "showFallbackMonogram", "");
  url = AppendQueryParameter(url, "pageUrl",
                             GetCurrentSiteURL().GetWithoutFilename().spec());

  if (refresh) {
    url = AppendQueryParameter(
        url, "v",
        base::UTF16ToUTF8(base::FormatNumber(
            base::Time::Now().InMillisecondsFSinceUnixEpoch())));
  }

  return url;
}

mojom::AdBlockMode CatsxpShieldsTabHelper::GetAdBlockMode() {
  return catsxp_shields_settings_->GetAdBlockMode(GetCurrentSiteURL());
}

mojom::FingerprintMode CatsxpShieldsTabHelper::GetFingerprintMode() {
  return catsxp_shields_settings_->GetFingerprintMode(GetCurrentSiteURL());
}

mojom::CookieBlockMode CatsxpShieldsTabHelper::GetCookieBlockMode() {
  auto cookie_settings = CookieSettingsFactory::GetForProfile(
      Profile::FromBrowserContext(web_contents()->GetBrowserContext()));

  const ControlType control_type = catsxp_shields::GetCookieControlType(
      &*host_content_settings_map_, cookie_settings.get(), GetCurrentSiteURL());

  switch (control_type) {
    case ControlType::ALLOW:
      return mojom::CookieBlockMode::ALLOW;
    case ControlType::BLOCK_THIRD_PARTY:
      return mojom::CookieBlockMode::CROSS_SITE_BLOCKED;
    case ControlType::BLOCK:
      return mojom::CookieBlockMode::BLOCKED;
    case ControlType::DEFAULT:
      break;
  }
  NOTREACHED() << "Unexpected value for control_type: "
               << std::to_underlying(control_type);
}

mojom::HttpsUpgradeMode CatsxpShieldsTabHelper::GetHttpsUpgradeMode() {
  ControlType control_type = catsxp_shields::GetHttpsUpgradeControlType(
      &*host_content_settings_map_, GetCurrentSiteURL());
  if (control_type == ControlType::ALLOW) {
    return mojom::HttpsUpgradeMode::DISABLED_MODE;
  } else if (control_type == ControlType::BLOCK) {
    return mojom::HttpsUpgradeMode::STRICT_MODE;
  } else if (control_type == ControlType::BLOCK_THIRD_PARTY) {
    return mojom::HttpsUpgradeMode::STANDARD_MODE;
  } else {
    return mojom::HttpsUpgradeMode::STANDARD_MODE;
  }
}

bool CatsxpShieldsTabHelper::GetNoScriptEnabled() {
  return catsxp_shields_settings_->IsNoScriptEnabled(GetCurrentSiteURL());
}

mojom::ContentSettingsOverriddenDataPtr
CatsxpShieldsTabHelper::GetJsContentSettingsOverriddenData() {
  return catsxp_shields_settings_->GetJsContentSettingOverriddenData(
      GetCurrentSiteURL());
}

bool CatsxpShieldsTabHelper::GetForgetFirstPartyStorageEnabled() {
  return catsxp_shields_settings_->GetForgetFirstPartyStorageEnabled(
      GetCurrentSiteURL());
}

void CatsxpShieldsTabHelper::SetAdBlockMode(mojom::AdBlockMode mode) {
  catsxp_shields_settings_->SetAdBlockMode(mode, GetCurrentSiteURL());

  ReloadWebContents();
}

void CatsxpShieldsTabHelper::SetFingerprintMode(mojom::FingerprintMode mode) {
  catsxp_shields_settings_->SetFingerprintMode(mode, GetCurrentSiteURL());

  ReloadWebContents();
}

void CatsxpShieldsTabHelper::SetCookieBlockMode(mojom::CookieBlockMode mode) {
  auto* prefs = Profile::FromBrowserContext(web_contents()->GetBrowserContext())
                    ->GetPrefs();
  ControlType control_type = ControlType::BLOCK;

  switch (mode) {
    case mojom::CookieBlockMode::ALLOW:
      control_type = ControlType::ALLOW;
      break;
    case mojom::CookieBlockMode::CROSS_SITE_BLOCKED:
      control_type = ControlType::BLOCK_THIRD_PARTY;
      break;
    case mojom::CookieBlockMode::BLOCKED:
      control_type = ControlType::BLOCK;
      break;
  }

  catsxp_shields::SetCookieControlType(&*host_content_settings_map_, prefs,
                                      control_type, GetCurrentSiteURL(),
                                      g_browser_process->local_state());

  ReloadWebContents();
}

void CatsxpShieldsTabHelper::SetHttpsUpgradeMode(mojom::HttpsUpgradeMode mode) {
  ControlType control_type;
  if (mode == mojom::HttpsUpgradeMode::DISABLED_MODE) {
    control_type = ControlType::ALLOW;
  } else if (mode == mojom::HttpsUpgradeMode::STRICT_MODE) {
    control_type = ControlType::BLOCK;
  } else if (mode == mojom::HttpsUpgradeMode::STANDARD_MODE) {
    control_type = ControlType::BLOCK_THIRD_PARTY;
  } else {
    control_type = ControlType::DEFAULT;
  }
  catsxp_shields::SetHttpsUpgradeControlType(&*host_content_settings_map_,
                                            control_type, GetCurrentSiteURL(),
                                            g_browser_process->local_state());

  ReloadWebContents();
}

void CatsxpShieldsTabHelper::SetIsNoScriptEnabled(bool is_enabled) {
  catsxp_shields_settings_->SetNoScriptEnabled(is_enabled, GetCurrentSiteURL());

  ReloadWebContents();
}

void CatsxpShieldsTabHelper::SetForgetFirstPartyStorageEnabled(bool is_enabled) {
  catsxp_shields_settings_->SetForgetFirstPartyStorageEnabled(
      is_enabled, GetCurrentSiteURL());
}

void CatsxpShieldsTabHelper::BlockAllowedScripts(
    const std::vector<std::string>& origins) {
  CatsxpShieldsWebContentsObserver* observer =
      CatsxpShieldsWebContentsObserver::FromWebContents(web_contents());
  if (!observer) {
    return;
  }
  observer->BlockAllowedScripts(origins);
  ReloadWebContents();
}

void CatsxpShieldsTabHelper::EnforceSiteDataCleanup() {
  auto* site_instance = web_contents()->GetSiteInstance();
  CHECK(site_instance);

  if (!ephemeral_storage_service_) {
    return;
  }

  // Start manual cleanup.
  ephemeral_storage_service_->CleanupTLDFirstPartyStorage(
      web_contents()->GetLastCommittedURL(),
      site_instance->GetSecurityPrincipal().GetStoragePartitionConfig(), true);
}

void CatsxpShieldsTabHelper::AllowScriptsOnce(
    const std::vector<std::string>& origins) {
  CatsxpShieldsWebContentsObserver* observer =
      CatsxpShieldsWebContentsObserver::FromWebContents(web_contents());
  if (!observer) {
    return;
  }
  UMA_HISTOGRAM_BOOLEAN(kShieldsAllowScriptOnceHistogramName, true);
  observer->AllowScriptsOnce(origins);
  ReloadWebContents();
}

bool CatsxpShieldsTabHelper::IsCatsxpShieldsManaged() {
  PrefService* profile_prefs =
      Profile::FromBrowserContext(web_contents()->GetBrowserContext())
          ->GetPrefs();

  return catsxp_shields::IsCatsxpShieldsManaged(
      profile_prefs, &*host_content_settings_map_, GetCurrentSiteURL());
}

void CatsxpShieldsTabHelper::HandleItemBlocked(const std::string& block_type,
                                              const std::string& subresource) {
  auto subres = GURL(subresource);

  if (block_type == kAds) {
    resource_list_blocked_ads_.insert(subres);
  } else if (block_type == kHTTPUpgradableResources) {
    resource_list_http_redirects_.insert(subres);
  } else if (block_type == kJavaScript) {
    resource_list_blocked_js_.insert(subres);
  } else if (block_type == kFingerprintingV2) {
    resource_list_blocked_fingerprints_.insert(subres);
  }

  for (Observer& obs : observer_list_) {
    obs.OnResourcesChanged();
  }
}

void CatsxpShieldsTabHelper::HandleItemAllowedOnce(
    const std::string& allowed_once_type,
    const std::string& subresource) {
  GURL subres(subresource);
  if (allowed_once_type != kJavaScript) {
    return;
  }
  if (resource_list_allowed_once_js_.contains(subres)) {
    return;
  }
  resource_list_allowed_once_js_.insert(std::move(subres));

  for (Observer& obs : observer_list_) {
    obs.OnResourcesChanged();
  }
}

void CatsxpShieldsTabHelper::HandleWebcompatFeatureInvoked(
    ContentSettingsType webcompat_content_settings) {
  if (webcompat_content_settings > ContentSettingsType::CATSXP_WEBCOMPAT_NONE &&
      webcompat_content_settings < ContentSettingsType::CATSXP_WEBCOMPAT_ALL) {
    webcompat_features_invoked_.insert(webcompat_content_settings);
  }

  for (Observer& obs : observer_list_) {
    obs.OnResourcesChanged();
  }
}

void CatsxpShieldsTabHelper::SetWebcompatEnabled(
    ContentSettingsType webcompat_settings_type,
    bool enabled) {
  catsxp_shields::SetWebcompatEnabled(
      &*host_content_settings_map_, webcompat_settings_type, enabled,
      GetCurrentSiteURL(), g_browser_process->local_state());
  ReloadWebContents();
}

base::flat_map<ContentSettingsType, bool>
CatsxpShieldsTabHelper::GetWebcompatSettings() {
  const GURL& current_site_url = GetCurrentSiteURL();
  base::flat_map<ContentSettingsType, bool> result;
  for (auto webcompat_settings_type = ContentSettingsType::CATSXP_WEBCOMPAT_NONE;
       webcompat_settings_type != ContentSettingsType::CATSXP_WEBCOMPAT_ALL;
       webcompat_settings_type = static_cast<ContentSettingsType>(
           static_cast<int32_t>(webcompat_settings_type) + 1)) {
    const bool enabled = catsxp_shields::IsWebcompatEnabled(
        &*host_content_settings_map_, webcompat_settings_type,
        current_site_url);
    result[webcompat_settings_type] = enabled;
  }
  return result;
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(CatsxpShieldsTabHelper);

}  // namespace catsxp_shields
