/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TEST_CONVERSIONS_TEST_CONSTANTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TEST_CONVERSIONS_TEST_CONSTANTS_H_

namespace catsxp_ads::test {

// Default conversion.
inline constexpr char kMatchingUrlPattern[] = "https://foo.com/*";
inline constexpr char kAnotherMatchingUrlPattern[] = "https://qux.com/*/corge";
inline constexpr char kMismatchingUrlPattern[] =
    "https://www.grault.com/garply";

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_TEST_CONVERSIONS_TEST_CONSTANTS_H_
