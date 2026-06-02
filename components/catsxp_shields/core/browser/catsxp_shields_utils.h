/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_CATSXP_SHIELDS_UTILS_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_CATSXP_SHIELDS_UTILS_H_

#include <string>

#include "base/containers/span.h"
#include "catsxp/components/catsxp_shields/core/common/catsxp_shields_panel.mojom-data-view.h"
#include "catsxp/components/catsxp_shields/core/common/catsxp_shields_settings_values.h"
#include "catsxp/components/catsxp_shields/core/common/shields_settings.mojom.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "components/content_settings/core/common/content_settings_types.h"

namespace https_upgrade_exceptions {
class HttpsUpgradeExceptionsService;
}

namespace content_settings {
class CookieSettings;
}

class GURL;
class HostContentSettingsMap;
class PrefService;

namespace catsxp_shields {

// List of possible blocking modes when accessing blocked websites.
enum class DomainBlockingType {
  // Don't block a website, open as is.
  kNone,
  // Proceed to a website, but use Ephemeral Storage for privacy-sensitive data
  // (cookies, etc.).
  k1PES,
  // Show an interstitial before proceeding to as website.
  kAggressive,
};

ContentSettingsPattern GetPatternFromURL(const GURL& url);
std::string ControlTypeToString(ControlType type);
ControlType ControlTypeFromString(const std::string& string);

void SetCatsxpShieldsEnabled(HostContentSettingsMap* map,
                            bool enable,
                            const GURL& url,
                            PrefService* local_state = nullptr);
bool GetCatsxpShieldsEnabled(HostContentSettingsMap* map, const GURL& url);

void SetAdControlType(HostContentSettingsMap* map,
                      ControlType type,
                      const GURL& url,
                      PrefService* local_state = nullptr);
ControlType GetAdControlType(HostContentSettingsMap* map, const GURL& url);

void SetCosmeticFilteringControlType(HostContentSettingsMap* map,
                                     ControlType type,
                                     const GURL& url,
                                     PrefService* local_state = nullptr,
                                     PrefService* profile_state = nullptr);
ControlType GetCosmeticFilteringControlType(HostContentSettingsMap* map,
                                            const GURL& url);
bool IsFirstPartyCosmeticFilteringEnabled(HostContentSettingsMap* map,
                                          const GURL& url);

bool IsReduceLanguageEnabledForProfile(PrefService* pref_service);

bool ShouldDoReduceLanguage(HostContentSettingsMap* map,
                            const GURL& url,
                            PrefService* pref_service);

DomainBlockingType GetDomainBlockingType(HostContentSettingsMap* map,
                                         const GURL& url);

void SetCookieControlType(HostContentSettingsMap* map,
                          PrefService* profile_state,
                          ControlType type,
                          const GURL& url,
                          PrefService* local_state = nullptr);
ControlType GetCookieControlType(
    HostContentSettingsMap* map,
    content_settings::CookieSettings* cookie_settings,
    const GURL& url);

void SetFingerprintingControlType(HostContentSettingsMap* map,
                                  ControlType type,
                                  const GURL& url,
                                  PrefService* local_state = nullptr,
                                  PrefService* profile_state = nullptr);
ControlType GetFingerprintingControlType(HostContentSettingsMap* map,
                                         const GURL& url);

bool IsCatsxpShieldsManaged(PrefService* prefs,
                           HostContentSettingsMap* map,
                           GURL url);

void SetHttpsUpgradeControlType(HostContentSettingsMap* map,
                                ControlType type,
                                const GURL& url,
                                PrefService* local_state = nullptr);
ControlType GetHttpsUpgradeControlType(HostContentSettingsMap* map,
                                       const GURL& url);
bool ShouldUpgradeToHttps(
    HostContentSettingsMap* map,
    const GURL& url,
    https_upgrade_exceptions::HttpsUpgradeExceptionsService*
        https_upgrade_exceptions_service);
bool ShouldForceHttps(HostContentSettingsMap* map, const GURL& url);

bool IsShowStrictFingerprintingModeEnabled();

void SetNoScriptControlType(HostContentSettingsMap* map,
                            ControlType type,
                            const GURL& url,
                            PrefService* local_state = nullptr);
ControlType GetNoScriptControlType(HostContentSettingsMap* map,
                                   const GURL& url);

// Enables a webcompat exception for a specific URL.
void SetWebcompatEnabled(HostContentSettingsMap* map,
                         ContentSettingsType webcompat_settings_type,
                         bool enabled,
                         const GURL& url,
                         PrefService* local_state);

bool IsWebcompatEnabled(HostContentSettingsMap* map,
                        ContentSettingsType webcompat_settings_type,
                        const GURL& url);

mojom::FarblingLevel GetFarblingLevel(HostContentSettingsMap* map,
                                      const GURL& primary_url);
base::Token GetFarblingToken(HostContentSettingsMap* map,
                             const GURL& url,
                             base::span<const uint8_t> additional_entropy);

bool IsDeveloperModeEnabled(PrefService* profile_state);

void SetAllowElementBlockerInPrivateModeEnabled(PrefService* local_state,
                                                bool value);
bool GetAllowElementBlockerInPrivateModeEnabled(PrefService* local_state);

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_CATSXP_SHIELDS_UTILS_H_
