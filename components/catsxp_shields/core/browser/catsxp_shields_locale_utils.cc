/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_locale_utils.h"

#include "base/feature_list.h"
#include "base/strings/string_util.h"
#include "catsxp/components/catsxp_shields/core/common/catsxp_shield_constants.h"
#include "catsxp/components/catsxp_shields/core/common/features.h"
#include "catsxp/components/catsxp_shields/core/common/pref_names.h"
#include "components/prefs/pref_service.h"

namespace catsxp_shields {

std::string GetLanguageCodeFromLocale(const std::string& locale) {
  const std::string::size_type loc = locale.find("-");
  if (loc == std::string::npos) {
    return base::ToLowerASCII(locale);
  }
  return base::ToLowerASCII(locale.substr(0, loc));
}

bool IsAdblockOnlyModeSupportedForLocale(const std::string& locale) {
  return kAdblockOnlyModeSupportedLanguageCodes.contains(
      GetLanguageCodeFromLocale(locale));
}

void ManageAdBlockOnlyModeByLocale(PrefService* local_state,
                                   const std::string& locale) {
  if (!base::FeatureList::IsEnabled(
          catsxp_shields::features::kAdblockOnlyMode)) {
    return;
  }

  if (!IsAdblockOnlyModeSupportedForLocale(locale)) {
    // If the current locale is not supported and Ad Block Only mode is enabled,
    // then disable Ad Block Only mode and set
    // `catsxp.shields.adblock_only_mode_was_enabled_for_supported_locale` pref
    // value to true.
    if (local_state->GetBoolean(prefs::kAdBlockOnlyModeEnabled)) {
      local_state->SetBoolean(prefs::kAdBlockOnlyModeEnabled, false);
      local_state->SetBoolean(
          prefs::kAdBlockOnlyModeWasEnabledForSupportedLocale, true);
    }
  } else {
    // If the current locale is supported, Ad Block Only mode is not enabled and
    // was enabled previously for a supported locale, enable it.
    if (!local_state->GetBoolean(prefs::kAdBlockOnlyModeEnabled) &&
        local_state->GetBoolean(
            prefs::kAdBlockOnlyModeWasEnabledForSupportedLocale)) {
      local_state->SetBoolean(prefs::kAdBlockOnlyModeEnabled, true);
      local_state->SetBoolean(
          prefs::kAdBlockOnlyModeWasEnabledForSupportedLocale, false);
    }
  }
}

}  // namespace catsxp_shields
