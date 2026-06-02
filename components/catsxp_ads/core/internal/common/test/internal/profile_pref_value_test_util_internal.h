/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_PROFILE_PREF_VALUE_TEST_UTIL_INTERNAL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_PROFILE_PREF_VALUE_TEST_UTIL_INTERNAL_H_

#include <string>

#include "base/values.h"

namespace catsxp_ads::test {

base::Value GetProfilePrefValue(const std::string& path);

base::Value GetDefaultProfilePrefValue(const std::string& path);

void ClearProfilePrefValue(const std::string& path);

bool HasProfilePrefPathValue(const std::string& path);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_PROFILE_PREF_VALUE_TEST_UTIL_INTERNAL_H_
