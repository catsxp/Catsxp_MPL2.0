/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TEST_CONVERSIONS_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TEST_CONVERSIONS_TEST_UTIL_H_

#include <vector>

class GURL;

namespace catsxp_ads::test {

// Default conversion.
std::vector<GURL> BuildDefaultConversionRedirectChain();

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TEST_CONVERSIONS_TEST_UTIL_H_
