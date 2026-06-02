/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_CURRENT_TEST_UTIL_INTERNAL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_CURRENT_TEST_UTIL_INTERNAL_H_

#include <string>

namespace catsxp_ads::test {

std::string GetUuidForCurrentTest();
std::string GetUuidForCurrentTestAndValue(const std::string& value);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_CURRENT_TEST_UTIL_INTERNAL_H_
