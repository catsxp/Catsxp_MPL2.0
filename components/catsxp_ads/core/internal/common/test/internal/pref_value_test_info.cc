/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/pref_value_test_info.h"

namespace catsxp_ads::test {

PrefValueInfo::PrefValueInfo() = default;

PrefValueInfo::PrefValueInfo(const PrefValueInfo& other) {
  *this = other;
}

PrefValueInfo& PrefValueInfo::operator=(const PrefValueInfo& other) {
  if (this != &other) {
    default_value = other.default_value.Clone();
    if (other.value) {
      value = other.value->Clone();
    }
  }

  return *this;
}

PrefValueInfo::PrefValueInfo(PrefValueInfo&& other) noexcept = default;

PrefValueInfo& PrefValueInfo::operator=(PrefValueInfo&& other) noexcept =
    default;

PrefValueInfo::~PrefValueInfo() = default;

}  // namespace catsxp_ads::test
