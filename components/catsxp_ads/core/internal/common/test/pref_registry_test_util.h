/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_PREF_REGISTRY_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_PREF_REGISTRY_TEST_UTIL_H_

namespace catsxp_ads::test {

// TODO(https://github.com/catsxp/catsxp-browser/issues/34528): Refactor unit test
// pref mocks to use PrefService.

void RegisterLocalStatePrefs();
void RegisterProfilePrefs();

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_PREF_REGISTRY_TEST_UTIL_H_
