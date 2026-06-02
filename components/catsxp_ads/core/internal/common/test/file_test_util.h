/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_FILE_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_FILE_TEST_UTIL_H_

#include <optional>
#include <string>

namespace catsxp_ads::test {

std::optional<std::string> MaybeReadFileToString(const std::string& name);

// The file can include `<time:period>` tags for mocking timestamps. `period`
// can be one of the following: `now`, `distant_past`, `distant_future`, `+/-#
// seconds`, `+/-# minutes`, `+/-# hours`, or `+/-# days`, i.e.,
//
//     `<time:+7 days>`
std::optional<std::string> MaybeReadFileToStringAndReplaceTags(
    const std::string& name);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_FILE_TEST_UTIL_H_
