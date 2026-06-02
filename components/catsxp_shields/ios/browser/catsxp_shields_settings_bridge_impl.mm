/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/ios/browser/catsxp_shields_settings_bridge_impl.h"

#include <Foundation/Foundation.h>

#include <memory>

#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_settings_service.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/prefs/pref_service.h"
#include "net/base/apple/url_conversions.h"
#include "url/gurl.h"

@implementation CatsxpShieldsSettingsBridgeImpl {
  raw_ptr<catsxp_shields::CatsxpShieldsSettingsService> _catsxpShieldsSettings;
}

- (instancetype)initWithCatsxpShieldsSettings:
    (raw_ptr<catsxp_shields::CatsxpShieldsSettingsService>)catsxpShieldsSettings {
  if ((self = [super init])) {
    _catsxpShieldsSettings = catsxpShieldsSettings;
  }
  return self;
}

- (bool)catsxpShieldsEnabledFor:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  return _catsxpShieldsSettings->GetCatsxpShieldsEnabled(gurl);
}

- (void)setCatsxpShieldsEnabled:(bool)isEnabled forURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  _catsxpShieldsSettings->SetCatsxpShieldsEnabled(isEnabled, gurl);
}

- (CatsxpShieldsAdBlockMode)defaultAdBlockMode {
  return static_cast<CatsxpShieldsAdBlockMode>(
      _catsxpShieldsSettings->GetDefaultAdBlockMode());
}

- (CatsxpShieldsAdBlockMode)adBlockModeForURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  return static_cast<CatsxpShieldsAdBlockMode>(
      _catsxpShieldsSettings->GetAdBlockMode(gurl));
}

- (void)setDefaultAdBlockMode:(CatsxpShieldsAdBlockMode)adBlockMode {
  _catsxpShieldsSettings->SetDefaultAdBlockMode(
      static_cast<catsxp_shields::mojom::AdBlockMode>(adBlockMode));
}

- (void)setAdBlockMode:(CatsxpShieldsAdBlockMode)adBlockMode forURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  _catsxpShieldsSettings->SetAdBlockMode(
      static_cast<catsxp_shields::mojom::AdBlockMode>(adBlockMode), gurl);
}

- (bool)isBlockScriptsEnabledByDefault {
  return _catsxpShieldsSettings->IsNoScriptEnabledByDefault();
}

- (bool)blockScriptsEnabledForURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  return _catsxpShieldsSettings->IsNoScriptEnabled(gurl);
}

- (void)setBlockScriptsEnabledByDefault:(bool)isEnabled {
  _catsxpShieldsSettings->SetNoScriptEnabledByDefault(isEnabled);
}

- (void)setBlockScriptsEnabled:(bool)isEnabled forURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  _catsxpShieldsSettings->SetNoScriptEnabled(isEnabled, gurl);
}

- (CatsxpShieldsFingerprintMode)defaultFingerprintMode {
  return static_cast<CatsxpShieldsFingerprintMode>(
      _catsxpShieldsSettings->GetDefaultFingerprintMode());
}

- (CatsxpShieldsFingerprintMode)fingerprintModeForURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  return static_cast<CatsxpShieldsFingerprintMode>(
      _catsxpShieldsSettings->GetFingerprintMode(gurl));
}

- (void)setDefaultFingerprintMode:(CatsxpShieldsFingerprintMode)fingerprintMode {
  _catsxpShieldsSettings->SetDefaultFingerprintMode(
      static_cast<catsxp_shields::mojom::FingerprintMode>(fingerprintMode));
}

- (void)setFingerprintMode:(CatsxpShieldsFingerprintMode)fingerprintMode
                    forURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  _catsxpShieldsSettings->SetFingerprintMode(
      static_cast<catsxp_shields::mojom::FingerprintMode>(fingerprintMode),
      gurl);
}

- (CatsxpShieldsAutoShredMode)defaultAutoShredMode {
  return static_cast<CatsxpShieldsAutoShredMode>(
      _catsxpShieldsSettings->GetDefaultAutoShredMode());
}

- (CatsxpShieldsAutoShredMode)autoShredModeForURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  return static_cast<CatsxpShieldsAutoShredMode>(
      _catsxpShieldsSettings->GetAutoShredMode(gurl));
}

- (void)setDefaultAutoShredMode:(CatsxpShieldsAutoShredMode)autoShredMode {
  _catsxpShieldsSettings->SetDefaultAutoShredMode(
      static_cast<catsxp_shields::mojom::AutoShredMode>(autoShredMode));
}

- (void)setAutoShredMode:(CatsxpShieldsAutoShredMode)autoShredMode
                  forURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  _catsxpShieldsSettings->SetAutoShredMode(
      static_cast<catsxp_shields::mojom::AutoShredMode>(autoShredMode), gurl);
}

- (BOOL)isShieldsDisabledOnAnyHostMatchingDomainOf:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  return _catsxpShieldsSettings->IsShieldsDisabledOnAnyHostMatchingDomainOf(
      gurl);
}

@end
