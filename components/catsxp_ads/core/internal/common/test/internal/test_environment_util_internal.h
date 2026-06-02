/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_TEST_ENVIRONMENT_UTIL_INTERNAL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_TEST_ENVIRONMENT_UTIL_INTERNAL_H_

// Internal helpers for configuring global test environment state that is only
// needed during `TestBase` setup.

namespace catsxp_ads::test {

void SetUpCommandLineSwitches();

void SetUpContentSettings();

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_TEST_ENVIRONMENT_UTIL_INTERNAL_H_
