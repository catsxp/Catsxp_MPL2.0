/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_CATSXP_SHIELDS_LOCALE_UTILS_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_CATSXP_SHIELDS_LOCALE_UTILS_H_

#include <string>

class PrefService;

namespace catsxp_shields {

std::string GetLanguageCodeFromLocale(const std::string& locale);

bool IsAdblockOnlyModeSupportedForLocale(const std::string& locale);

// The following function enables or disables Ad Block Only mode based on the
// locale. If the locale is not supported, it disables Ad Block Only mode and
// sets `catsxp.shields.adblock_only_mode_was_enabled_for_supported_locale` pref
// value to true.
// If the locale is supported, it enables Ad Block Only mode if it was
// enabled previously for a supported locale.
void ManageAdBlockOnlyModeByLocale(PrefService* local_state,
                                   const std::string& locale);

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_CATSXP_SHIELDS_LOCALE_UTILS_H_
