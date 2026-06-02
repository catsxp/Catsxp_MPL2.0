/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_SCOPED_TIMEZONE_FOR_TESTING_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_SCOPED_TIMEZONE_FOR_TESTING_H_

#include <string>
#include <string_view>

#include "base/test/icu_test_util.h"
#include "base/test/scoped_libc_timezone_override.h"

namespace catsxp_ads::test {

// Scoped wrapper that sets both ICU and libc timezones for cross-platform use.
//
// Not thread safe.

class ScopedTimezoneForTesting final {
 public:
  explicit ScopedTimezoneForTesting(std::string_view timezone)
      : timezone_(timezone), libc_(timezone_), icu_(timezone_.c_str()) {}

  ScopedTimezoneForTesting(const ScopedTimezoneForTesting&) = delete;
  ScopedTimezoneForTesting& operator=(const ScopedTimezoneForTesting&) = delete;

  ~ScopedTimezoneForTesting() = default;

 private:
  const std::string timezone_;
  const base::test::ScopedLibcTimezoneOverride libc_;
  const base::test::ScopedRestoreDefaultTimezone icu_;
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_SCOPED_TIMEZONE_FOR_TESTING_H_
