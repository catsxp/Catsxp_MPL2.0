/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_FILE_PATH_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_FILE_PATH_TEST_UTIL_H_

namespace base {
class FilePath;
}  // namespace base

namespace catsxp_ads::test {

// Returns the path to the `components/catsxp_ads/core/test/data` directory,
// which contains all mocked data.
base::FilePath DataPath();

// Returns the path to the
// `components/catsxp_ads/core/test/data/resources/components` directory, which
// contains mocked resource components.
base::FilePath ResourceComponentsDataPath();

// Provides the path to the `components/catsxp_ads/core/test/data/url_responses`
// directory, which contains mocked URL responses for use with
// `MockUrlResponses`.
base::FilePath UrlResponsesDataPath();

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_FILE_PATH_TEST_UTIL_H_
