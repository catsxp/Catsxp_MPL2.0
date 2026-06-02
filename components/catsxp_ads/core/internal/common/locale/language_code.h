/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_LOCALE_LANGUAGE_CODE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_LOCALE_LANGUAGE_CODE_H_

#include <optional>
#include <string>

namespace catsxp_ads {

// Return the current language of the device as string.
std::optional<std::string> MaybeGetLanguageCodeString();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_LOCALE_LANGUAGE_CODE_H_
