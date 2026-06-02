/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/test/subdivision_test_util.h"

#include "base/strings/string_util.h"

namespace catsxp_ads::test {

std::string BuildSubdivision(const std::string& country_code,
                             const std::string& subdivision_code) {
  return base::ReplaceStringPlaceholders(
      "$1-$2", {country_code, subdivision_code}, nullptr);
}

}  // namespace catsxp_ads::test
