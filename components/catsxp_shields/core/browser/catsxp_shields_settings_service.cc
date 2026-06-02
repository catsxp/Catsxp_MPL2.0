/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_settings_service.h"

#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_p3a.h"
#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_utils.h"
#include "catsxp/components/catsxp_shields/core/common/catsxp_shield_utils.h"
#include "catsxp/components/catsxp_shields/core/common/features.h"
#include "catsxp/components/catsxp_shields/core/common/pref_names.h"
#include "catsxp/components/content_settings/core/common/content_settings_util.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/prefs/pref_service.h"
#include "net/base/url_util.h"
#include "url/gurl.h"

namespace catsxp_shields {

CatsxpShieldsSettingsService::CatsxpShieldsSettingsService(
    HostContentSettingsMap& host_content_settings_map,
    PrefService* local_state,
    PrefService* profile_prefs)
    : host_content_settings_map_(host_content_settings_map),
      local_state_(local_state),
      profile_prefs_(profile_prefs) {
  CHECK(profile_prefs_);
}

CatsxpShieldsSettingsService::~CatsxpShieldsSettingsService() = default;

void CatsxpShieldsSettingsService::SetCatsxpShieldsEnabled(bool is_enabled,
                                                         const GURL& url) {
  catsxp_shields::SetCatsxpShieldsEnabled(&*host_content_settings_map_,
                                        is_enabled, url, local_state_);
}

bool CatsxpShieldsSettingsService::GetCatsxpShieldsEnabled(const GURL& url) {
  return catsxp_shields::GetCatsxpShieldsEnabled(&*host_content_settings_map_,
                                               url);
}

void CatsxpShieldsSettingsService::SetDefaultAdBlockMode(
    mojom::AdBlockMode mode) {
  SetAdBlockMode(mode, GURL());
}

mojom::AdBlockMode CatsxpShieldsSettingsService::GetDefaultAdBlockMode() {
  return GetAdBlockMode(GURL());
}

void CatsxpShieldsSettingsService::SetAdBlockMode(mojom::AdBlockMode mode,
                                                 const GURL& url) {
  ControlType control_type_ad;
  ControlType control_type_cosmetic;

  if (mode == mojom::AdBlockMode::ALLOW) {
    control_type_ad = ControlType::ALLOW;
  } else {
    control_type_ad = ControlType::BLOCK;
  }

  if (mode == mojom::AdBlockMode::AGGRESSIVE) {
    control_type_cosmetic = ControlType::BLOCK;  // aggressive
  } else if (mode == mojom::AdBlockMode::STANDARD) {
    control_type_cosmetic = ControlType::BLOCK_THIRD_PARTY;  // standard
  } else {
    control_type_cosmetic = ControlType::ALLOW;  // allow
  }

  catsxp_shields::SetAdControlType(&*host_content_settings_map_, control_type_ad,
                                  url, local_state_);

  catsxp_shields::SetCosmeticFilteringControlType(&*host_content_settings_map_,
                                                 control_type_cosmetic, url,
                                                 local_state_, profile_prefs_);
}

mojom::AdBlockMode CatsxpShieldsSettingsService::GetAdBlockMode(
    const GURL& url) {
  ControlType control_type_ad =
      catsxp_shields::GetAdControlType(&*host_content_settings_map_, url);

  ControlType control_type_cosmetic =
      catsxp_shields::GetCosmeticFilteringControlType(
          &*host_content_settings_map_, url);

  if (control_type_ad == ControlType::ALLOW) {
    return mojom::AdBlockMode::ALLOW;
  }

  if (control_type_cosmetic == ControlType::BLOCK) {
    return mojom::AdBlockMode::AGGRESSIVE;
  } else {
    return mojom::AdBlockMode::STANDARD;
  }
}

void CatsxpShieldsSettingsService::SetDefaultFingerprintMode(
    mojom::FingerprintMode mode) {
  SetFingerprintMode(mode, GURL());
}

mojom::FingerprintMode
CatsxpShieldsSettingsService::GetDefaultFingerprintMode() {
  return GetFingerprintMode(GURL());
}

void CatsxpShieldsSettingsService::SetFingerprintMode(
    mojom::FingerprintMode mode,
    const GURL& url) {
#if BUILDFLAG(IS_IOS)
  /// Strict FingerprintMode is not supported on iOS
  CHECK(mode != mojom::FingerprintMode::STRICT_MODE);
#endif

  ControlType control_type;

  if (mode == mojom::FingerprintMode::ALLOW_MODE) {
    control_type = ControlType::ALLOW;
  } else if (mode == mojom::FingerprintMode::STRICT_MODE) {
    control_type = ControlType::BLOCK;
  } else {
    control_type = ControlType::DEFAULT;  // STANDARD_MODE
  }

  catsxp_shields::SetFingerprintingControlType(&*host_content_settings_map_,
                                              control_type, url, local_state_,
                                              profile_prefs_);
}

mojom::FingerprintMode CatsxpShieldsSettingsService::GetFingerprintMode(
    const GURL& url) {
  ControlType control_type = catsxp_shields::GetFingerprintingControlType(
      &*host_content_settings_map_, url);

  if (control_type == ControlType::ALLOW) {
    return mojom::FingerprintMode::ALLOW_MODE;
  } else if (control_type == ControlType::BLOCK) {
#if BUILDFLAG(IS_IOS)
    /// Strict FingerprintMode is not supported on iOS.
    /// In case of sync'd setting, return standard mode.
    return mojom::FingerprintMode::STANDARD_MODE;
#else
    return mojom::FingerprintMode::STRICT_MODE;
#endif
  } else {
    return mojom::FingerprintMode::STANDARD_MODE;
  }
}

void CatsxpShieldsSettingsService::SetNoScriptEnabledByDefault(bool is_enabled) {
  SetNoScriptEnabled(is_enabled, GURL());
}

bool CatsxpShieldsSettingsService::IsNoScriptEnabledByDefault() {
  return IsNoScriptEnabled(GURL());
}

void CatsxpShieldsSettingsService::SetNoScriptEnabled(bool is_enabled,
                                                     const GURL& url) {
  ControlType control_type =
      is_enabled ? ControlType::BLOCK : ControlType::ALLOW;
  catsxp_shields::SetNoScriptControlType(&*host_content_settings_map_,
                                        control_type, url, local_state_);
}

bool CatsxpShieldsSettingsService::IsNoScriptEnabled(const GURL& url) {
  ControlType control_type =
      catsxp_shields::GetNoScriptControlType(&*host_content_settings_map_, url);

  return control_type != ControlType::ALLOW;
}

#if !BUILDFLAG(IS_IOS)
bool CatsxpShieldsSettingsService::GetForgetFirstPartyStorageEnabled(
    const GURL& url) {
  ContentSetting setting = host_content_settings_map_->GetContentSetting(
      url, url, ContentSettingsType::CATSXP_REMEMBER_1P_STORAGE);

  return setting == CONTENT_SETTING_BLOCK;
}

void CatsxpShieldsSettingsService::SetForgetFirstPartyStorageEnabled(
    bool is_enabled,
    const GURL& url) {
  auto primary_pattern = content_settings::CreateDomainPattern(url);

  if (!primary_pattern.IsValid()) {
    return;
  }

  host_content_settings_map_->SetContentSettingCustomScope(
      primary_pattern, ContentSettingsPattern::Wildcard(),
      ContentSettingsType::CATSXP_REMEMBER_1P_STORAGE,
      is_enabled ? CONTENT_SETTING_BLOCK : CONTENT_SETTING_ALLOW);

  MaybeRecordShieldsUsageP3A(kChangedPerSiteShields, local_state_);
  RecordForgetFirstPartySetting(&*host_content_settings_map_);
}
#endif

void CatsxpShieldsSettingsService::SetDefaultAutoShredMode(
    mojom::AutoShredMode mode) {
  SetAutoShredMode(mode, GURL());
}

mojom::AutoShredMode CatsxpShieldsSettingsService::GetDefaultAutoShredMode() {
  return GetAutoShredMode(GURL());
}

void CatsxpShieldsSettingsService::SetAutoShredMode(mojom::AutoShredMode mode,
                                                   const GURL& url) {
  CHECK(base::FeatureList::IsEnabled(
      catsxp_shields::features::kCatsxpShredFeature));

  // Shred and AutoShred delete data at the eTLD+1 boundary, because that’s
  // the Web’s cookie boundary, so we must use the domain pattern to align
  // with how browsers enforce storage boundaries.
  auto primary_pattern = content_settings::CreateDomainPattern(url);

  if (!primary_pattern.IsValid()) {
    return;
  }

  host_content_settings_map_->SetWebsiteSettingCustomScope(
      primary_pattern, ContentSettingsPattern::Wildcard(),
      AutoShredSetting::kContentSettingsType, AutoShredSetting::ToValue(mode));

  ReportAutoShredSettingsP3A(*host_content_settings_map_);
}

mojom::AutoShredMode CatsxpShieldsSettingsService::GetAutoShredMode(
    const GURL& url) {
  CHECK(base::FeatureList::IsEnabled(
      catsxp_shields::features::kCatsxpShredFeature));
  return AutoShredSetting::FromValue(
      host_content_settings_map_->GetWebsiteSetting(
          url, GURL(), AutoShredSetting::kContentSettingsType));
}

bool CatsxpShieldsSettingsService::IsJsBlockingEnforced(const GURL& url) {
  const auto js_content_settings_overridden_data =
      GetJsContentSettingOverriddenData(url);
  return js_content_settings_overridden_data &&
         js_content_settings_overridden_data->status ==
             ::ContentSetting::CONTENT_SETTING_BLOCK;
}

mojom::ContentSettingsOverriddenDataPtr
CatsxpShieldsSettingsService::GetJsContentSettingOverriddenData(
    const GURL& url) {
  content_settings::SettingInfo info;
  const auto rule = host_content_settings_map_->GetContentSetting(
      url, GURL(), content_settings::mojom::ContentSettingsType::JAVASCRIPT,
      &info);

  // No override
  if (info.source == content_settings::SettingSource::kUser) {
    return nullptr;
  }

  return mojom::ContentSettingsOverriddenData::New(
      rule, ConvertSettingsSource(info.source));
}

bool CatsxpShieldsSettingsService::IsShieldsDisabledOnAnyHostMatchingDomainOf(
    const GURL& url) const {
  // First check the exact domain
  if (CONTENT_SETTING_BLOCK ==
      host_content_settings_map_->GetContentSetting(
          url, GURL(), ContentSettingsType::CATSXP_SHIELDS)) {
    return true;
  }

  // Check parent domains by iterating through all shield settings
  ContentSettingsForOneType all_shield_settings =
      host_content_settings_map_->GetSettingsForOneType(
          ContentSettingsType::CATSXP_SHIELDS);

  const auto ephemeral_domain = net::URLToEphemeralStorageDomain(url);

  for (const auto& setting : all_shield_settings) {
    // Skip invalid patterns or settings that don't disable shields
    if (!setting.primary_pattern.IsValid() ||
        setting.setting_value != CONTENT_SETTING_BLOCK) {
      continue;
    }

    // Skip wildcard patterns that match all hosts
    if (setting.primary_pattern.MatchesAllHosts()) {
      return true;
    }

    if (const GURL pattern_url(setting.primary_pattern.ToRepresentativeUrl());
        pattern_url.is_valid() &&
        ephemeral_domain == net::URLToEphemeralStorageDomain(pattern_url)) {
      return true;
    }
  }

  return false;
}

void CatsxpShieldsSettingsService::SetShredBrowsingHistory(bool value) {
  profile_prefs_->SetBoolean(prefs::kShredBrowsingHistoryEnabled, value);
}

bool CatsxpShieldsSettingsService::IsShredBrowsingHistoryEnabled() {
  return profile_prefs_->GetBoolean(prefs::kShredBrowsingHistoryEnabled);
}

}  // namespace catsxp_shields
