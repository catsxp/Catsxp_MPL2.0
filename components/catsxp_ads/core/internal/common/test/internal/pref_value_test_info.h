/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_PREF_VALUE_TEST_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_PREF_VALUE_TEST_INFO_H_

#include <optional>

#include "base/values.h"

namespace catsxp_ads::test {

struct PrefValueInfo final {
  PrefValueInfo();

  PrefValueInfo(const PrefValueInfo&);
  PrefValueInfo& operator=(const PrefValueInfo&);

  PrefValueInfo(PrefValueInfo&&) noexcept;
  PrefValueInfo& operator=(PrefValueInfo&&) noexcept;

  ~PrefValueInfo();

  bool operator==(const PrefValueInfo&) const = default;

  std::optional<base::Value> value;
  base::Value default_value;
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_PREF_VALUE_TEST_INFO_H_
