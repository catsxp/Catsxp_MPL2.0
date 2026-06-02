/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_STRINGS_STRING_STRIP_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_STRINGS_STRING_STRIP_UTIL_H_

#include <string>

namespace catsxp_ads {

std::string StripNonAlphaCharacters(const std::string& value);
std::string StripNonAlphaNumericCharacters(const std::string& value);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_STRINGS_STRING_STRIP_UTIL_H_
