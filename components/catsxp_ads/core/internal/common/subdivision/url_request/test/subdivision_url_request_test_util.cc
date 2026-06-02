/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/test/subdivision_url_request_test_util.h"

#include "base/strings/string_util.h"

namespace catsxp_ads::test {

std::string BuildSubdivisionUrlResponseBody(
    const std::string& country_code,
    const std::string& subdivision_code) {
  return base::ReplaceStringPlaceholders(
      R"(
          {
            "country": "$1",
            "region": "$2"
          })",
      {country_code, subdivision_code}, nullptr);
}

}  // namespace catsxp_ads::test
