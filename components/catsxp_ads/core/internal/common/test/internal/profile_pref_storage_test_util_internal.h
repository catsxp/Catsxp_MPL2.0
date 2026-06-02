/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_PROFILE_PREF_STORAGE_TEST_UTIL_INTERNAL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_PROFILE_PREF_STORAGE_TEST_UTIL_INTERNAL_H_

#include <string>

namespace catsxp_ads::test {

struct PrefValueInfo;

bool FindProfilePref(const std::string& path);

PrefValueInfo& ProfilePref(const std::string& path);

bool HasProfilePref(const std::string& path);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_PROFILE_PREF_STORAGE_TEST_UTIL_INTERNAL_H_
