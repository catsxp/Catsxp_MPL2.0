/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_registry_test_util.h"

#include <utility>

#include "base/check.h"
#include "base/json/values_util.h"
#include "base/strings/string_number_conversions.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/pref_value_test_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/profile_pref_storage_test_util_internal.h"

namespace catsxp_ads::test {

void RegisterProfilePref(const std::string& path, base::Value default_value) {
  CHECK(!HasProfilePref(path))
      << "Trying to register a previously registered pref: " << path;

  ProfilePref(path).default_value = std::move(default_value);
}

void RegisterProfileBooleanPref(const std::string& path, bool default_value) {
  RegisterProfilePref(path, base::Value(default_value));
}

void RegisterProfileIntegerPref(const std::string& path, int default_value) {
  RegisterProfilePref(path, base::Value(default_value));
}

void RegisterProfileDoublePref(const std::string& path, double default_value) {
  RegisterProfilePref(path, base::Value(default_value));
}

void RegisterProfileStringPref(const std::string& path,
                               const std::string& default_value) {
  RegisterProfilePref(path, base::Value(default_value));
}

void RegisterProfileDictPref(const std::string& path,
                             base::DictValue default_value) {
  RegisterProfilePref(path, base::Value(std::move(default_value)));
}

void RegisterProfileListPref(const std::string& path,
                             base::ListValue default_value) {
  RegisterProfilePref(path, base::Value(std::move(default_value)));
}

void RegisterProfileInt64Pref(const std::string& path, int64_t default_value) {
  RegisterProfilePref(path, base::Int64ToValue(default_value));
}

void RegisterProfileUint64Pref(const std::string& path,
                               uint64_t default_value) {
  RegisterProfilePref(path, base::Value((base::NumberToString(default_value))));
}

void RegisterProfileTimePref(const std::string& path,
                             base::Time default_value) {
  RegisterProfilePref(path, base::TimeToValue(default_value));
}

void RegisterProfileTimeDeltaPref(const std::string& path,
                                  base::TimeDelta default_value) {
  RegisterProfilePref(path, base::TimeDeltaToValue(default_value));
}

}  // namespace catsxp_ads::test
