/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/profile_pref_storage_test_util_internal.h"

#include "base/containers/flat_map.h"
#include "base/no_destructor.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/current_test_util_internal.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/pref_value_test_info.h"

namespace catsxp_ads::test {

namespace {

base::flat_map</*uuid=*/std::string, PrefValueInfo>& ProfilePrefStorage() {
  static base::NoDestructor<base::flat_map<std::string, PrefValueInfo>> prefs;
  return *prefs;
}

}  // namespace

bool FindProfilePref(const std::string& path) {
  return ProfilePrefStorage().contains(GetUuidForCurrentTestAndValue(path));
}

PrefValueInfo& ProfilePref(const std::string& path) {
  const std::string uuid = GetUuidForCurrentTestAndValue(path);
  return ProfilePrefStorage()[uuid];
}

bool HasProfilePref(const std::string& path) {
  // Intentionally identical to `FindProfilePref`: the test double uses a
  // single map for both registration and storage, so both checks reduce to
  // the same `contains` lookup.
  return ProfilePrefStorage().contains(GetUuidForCurrentTestAndValue(path));
}

}  // namespace catsxp_ads::test
