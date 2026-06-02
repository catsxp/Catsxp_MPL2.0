/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/local_state_pref_value_test_util.h"

#include <utility>

#include "base/check.h"
#include "base/json/values_util.h"
#include "base/strings/string_number_conversions.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/local_state_pref_storage_test_util_internal.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/pref_value_test_info.h"

namespace catsxp_ads::test {

void SetLocalStatePrefValue(const std::string& path, base::Value value) {
  CHECK(HasLocalStatePref(path))
      << "Check failed. Trying to write an unregistered pref: " << path;

  LocalStatePref(path).value = std::move(value);
}

void SetDefaultLocalStatePrefValue(const std::string& path,
                                   base::Value default_value) {
  CHECK(HasLocalStatePref(path))
      << "Check failed. Trying to write an unregistered pref: " << path;

  LocalStatePref(path).default_value = std::move(default_value);
}

void SetLocalStateBooleanPrefValue(const std::string& path, bool value) {
  SetLocalStatePrefValue(path, base::Value(value));
}

void SetLocalStateIntegerPrefValue(const std::string& path, int value) {
  SetLocalStatePrefValue(path, base::Value(value));
}

void SetLocalStateDoublePrefValue(const std::string& path, double value) {
  SetLocalStatePrefValue(path, base::Value(value));
}

void SetLocalStateStringPrefValue(const std::string& path,
                                  const std::string& value) {
  SetLocalStatePrefValue(path, base::Value(value));
}

void SetLocalStateInt64PrefValue(const std::string& path, int64_t value) {
  SetLocalStatePrefValue(path, base::Int64ToValue(value));
}

void SetLocalStateUint64PrefValue(const std::string& path, uint64_t value) {
  SetLocalStatePrefValue(path, base::Value(base::NumberToString(value)));
}

void SetLocalStateDictPrefValue(const std::string& path,
                                base::DictValue value) {
  SetLocalStatePrefValue(path, base::Value(std::move(value)));
}

void SetLocalStateListPrefValue(const std::string& path,
                                base::ListValue value) {
  SetLocalStatePrefValue(path, base::Value(std::move(value)));
}

void SetLocalStateTimePrefValue(const std::string& path, base::Time value) {
  SetLocalStatePrefValue(path, base::TimeToValue(value));
}

}  // namespace catsxp_ads::test
