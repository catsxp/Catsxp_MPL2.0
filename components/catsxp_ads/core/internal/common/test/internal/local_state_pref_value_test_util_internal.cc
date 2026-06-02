/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/local_state_pref_value_test_util_internal.h"

#include <ostream>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/local_state_pref_storage_test_util_internal.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/pref_value_test_info.h"

namespace catsxp_ads::test {

base::Value GetLocalStatePrefValue(const std::string& path) {
  CHECK(HasLocalStatePref(path))
      << "Check failed. Trying to read an unregistered pref: " << path;

  const PrefValueInfo& pref = LocalStatePref(path);
  if (!pref.value) {
    return pref.default_value.Clone();
  }

  return pref.value->Clone();
}

base::Value GetDefaultLocalStatePrefValue(const std::string& path) {
  CHECK(HasLocalStatePref(path))
      << "Check failed. Trying to read an unregistered pref: " << path;

  return LocalStatePref(path).default_value.Clone();
}

void ClearLocalStatePrefValue(const std::string& path) {
  CHECK(HasLocalStatePref(path))
      << "Check failed. Trying to clear an unregistered pref: " << path;

  LocalStatePref(path).value.reset();
}

bool HasLocalStatePrefPathValue(const std::string& path) {
  CHECK(HasLocalStatePref(path))
      << "Check failed. Trying to read an unregistered pref: " << path;

  return !!LocalStatePref(path).value;
}

}  // namespace catsxp_ads::test
