/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/local_state_pref_storage_test_util_internal.h"

#include "base/containers/flat_map.h"
#include "base/no_destructor.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/current_test_util_internal.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/pref_value_test_info.h"

namespace catsxp_ads::test {

namespace {

base::flat_map</*uuid=*/std::string, PrefValueInfo>& LocalStatePrefStorage() {
  static base::NoDestructor<base::flat_map<std::string, PrefValueInfo>> prefs;
  return *prefs;
}

}  // namespace

bool FindLocalStatePref(const std::string& path) {
  const std::string uuid = GetUuidForCurrentTestAndValue(path);
  return LocalStatePrefStorage().contains(uuid);
}

PrefValueInfo& LocalStatePref(const std::string& path) {
  const std::string uuid = GetUuidForCurrentTestAndValue(path);
  return LocalStatePrefStorage()[uuid];
}

bool HasLocalStatePref(const std::string& path) {
  // Intentionally identical to `FindLocalStatePref`: the test double uses a
  // single map for both registration and storage, so both checks reduce to
  // the same `contains` lookup.
  return LocalStatePrefStorage().contains(GetUuidForCurrentTestAndValue(path));
}

}  // namespace catsxp_ads::test
