/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/content/browser/catsxp_farbling_service.h"

#include "base/check.h"
#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_utils.h"
#include "catsxp/components/catsxp_shields/core/common/pref_names.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "url/gurl.h"

namespace catsxp {

CatsxpFarblingService::CatsxpFarblingService(
    HostContentSettingsMap* host_content_settings_map)
    : host_content_settings_map_(host_content_settings_map) {
  DCHECK(host_content_settings_map_);
}

CatsxpFarblingService::~CatsxpFarblingService() = default;

bool CatsxpFarblingService::MakePseudoRandomGeneratorForURL(
    const GURL& url,
    base::span<const uint8_t> additional_entropy,
    FarblingPRNG* prng) {
  if (catsxp_shields::GetFarblingLevel(host_content_settings_map_, url) ==
      catsxp_shields::mojom::FarblingLevel::OFF) {
    return false;
  }
  const base::Token farbling_token = catsxp_shields::GetFarblingToken(
      host_content_settings_map_, url, additional_entropy);
  if (farbling_token.is_zero()) {
    return false;
  }
  *prng = FarblingPRNG(farbling_token.high() ^ farbling_token.low());
  return true;
}

// static
void CatsxpFarblingService::RegisterProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterBooleanPref(catsxp_shields::prefs::kReduceLanguageEnabled,
                                false);
}

}  // namespace catsxp
