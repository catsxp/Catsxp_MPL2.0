/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/profile_pref_value_test_util_internal.h"

#include <ostream>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/pref_value_test_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/profile_pref_storage_test_util_internal.h"

namespace catsxp_ads::test {

base::Value GetProfilePrefValue(const std::string& path) {
  CHECK(HasProfilePref(path))
      << "Check failed. Trying to read an unregistered pref: " << path;

  const PrefValueInfo& pref = ProfilePref(path);
  if (!pref.value) {
    return pref.default_value.Clone();
  }

  return pref.value->Clone();
}

base::Value GetDefaultProfilePrefValue(const std::string& path) {
  CHECK(HasProfilePref(path))
      << "Check failed. Trying to read an unregistered pref: " << path;

  return ProfilePref(path).default_value.Clone();
}

void ClearProfilePrefValue(const std::string& path) {
  CHECK(HasProfilePref(path))
      << "Check failed. Trying to clear an unregistered pref: " << path;

  ProfilePref(path).value.reset();
}

bool HasProfilePrefPathValue(const std::string& path) {
  CHECK(HasProfilePref(path))
      << "Check failed. Trying to read an unregistered pref: " << path;

  return !!ProfilePref(path).value;
}

}  // namespace catsxp_ads::test
