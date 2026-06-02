/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/current_test_util_internal.h"

#include "base/check.h"
#include "base/strings/string_util.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace catsxp_ads::test {

std::string GetUuidForCurrentTest() {
  const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();
  CHECK(test_info);

  return base::ReplaceStringPlaceholders(
      "$1.$2", {test_info->test_suite_name(), test_info->name()}, nullptr);
}

std::string GetUuidForCurrentTestAndValue(const std::string& value) {
  return base::ReplaceStringPlaceholders(
      "$1:$2", {value, GetUuidForCurrentTest()}, nullptr);
}

}  // namespace catsxp_ads::test
