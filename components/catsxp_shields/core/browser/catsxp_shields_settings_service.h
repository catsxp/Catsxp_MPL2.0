/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_CATSXP_SHIELDS_SETTINGS_SERVICE_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_CATSXP_SHIELDS_SETTINGS_SERVICE_H_

#include "base/memory/raw_ptr.h"
#include "base/memory/raw_ref.h"
#include "catsxp/components/catsxp_shields/core/common/catsxp_shields_panel.mojom.h"
#include "catsxp/components/catsxp_shields/core/common/shields_settings.mojom.h"
#include "components/content_settings/core/browser/cookie_settings.h"
#include "components/keyed_service/core/keyed_service.h"

class GURL;
class HostContentSettingsMap;
class PrefService;

namespace catsxp_shields {

class CatsxpShieldsSettingsService : public KeyedService {
 public:
  explicit CatsxpShieldsSettingsService(
      HostContentSettingsMap& host_content_settings_map,
      PrefService* local_state = nullptr,
      PrefService* profile_state = nullptr);
  ~CatsxpShieldsSettingsService() override;

  void SetCatsxpShieldsEnabled(bool enable, const GURL& url);
  bool GetCatsxpShieldsEnabled(const GURL& url);

  void SetDefaultAdBlockMode(mojom::AdBlockMode mode);
  mojom::AdBlockMode GetDefaultAdBlockMode();

  void SetAdBlockMode(mojom::AdBlockMode mode, const GURL& url);
  mojom::AdBlockMode GetAdBlockMode(const GURL& url);

  void SetDefaultFingerprintMode(mojom::FingerprintMode mode);
  mojom::FingerprintMode GetDefaultFingerprintMode();

  void SetFingerprintMode(mojom::FingerprintMode mode, const GURL& url);
  mojom::FingerprintMode GetFingerprintMode(const GURL& url);

  void SetNoScriptEnabledByDefault(bool is_enabled);
  bool IsNoScriptEnabledByDefault();

  void SetNoScriptEnabled(bool is_enabled, const GURL& url);
  bool IsNoScriptEnabled(const GURL& url);

#if !BUILDFLAG(IS_IOS)
  bool GetForgetFirstPartyStorageEnabled(const GURL& url);
  void SetForgetFirstPartyStorageEnabled(bool is_enabled, const GURL& url);
#endif

  void SetDefaultAutoShredMode(mojom::AutoShredMode mode);
  mojom::AutoShredMode GetDefaultAutoShredMode();

  void SetAutoShredMode(mojom::AutoShredMode mode, const GURL& url);
  mojom::AutoShredMode GetAutoShredMode(const GURL& url);

  bool IsJsBlockingEnforced(const GURL& url);
  mojom::ContentSettingsOverriddenDataPtr GetJsContentSettingOverriddenData(
      const GURL& url);

  bool IsShieldsDisabledOnAnyHostMatchingDomainOf(const GURL& url) const;

  void SetShredBrowsingHistory(bool value);
  bool IsShredBrowsingHistoryEnabled();

 private:
  const raw_ref<HostContentSettingsMap>
      host_content_settings_map_;       // NOT OWNED
  raw_ptr<PrefService> local_state_;    // NOT OWNED
  raw_ptr<PrefService> profile_prefs_;  // NOT OWNED
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_CATSXP_SHIELDS_SETTINGS_SERVICE_H_
