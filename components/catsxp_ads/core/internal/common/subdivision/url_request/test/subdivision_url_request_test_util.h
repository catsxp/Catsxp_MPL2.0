/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_TEST_SUBDIVISION_URL_REQUEST_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_TEST_SUBDIVISION_URL_REQUEST_TEST_UTIL_H_

#include <string>

namespace catsxp_ads::test {

std::string BuildSubdivisionUrlResponseBody(
    const std::string& country_code,
    const std::string& subdivision_code);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_TEST_SUBDIVISION_URL_REQUEST_TEST_UTIL_H_
