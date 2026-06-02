/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_LOCAL_STATE_PREF_REGISTRY_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_LOCAL_STATE_PREF_REGISTRY_TEST_UTIL_H_

#include <cstdint>
#include <string>

#include "base/values.h"

namespace base {
class Time;
class TimeDelta;
}  // namespace base

namespace catsxp_ads::test {

void RegisterLocalStatePref(const std::string& path, base::Value default_value);
void RegisterLocalStateBooleanPref(const std::string& path, bool default_value);
void RegisterLocalStateIntegerPref(const std::string& path, int default_value);
void RegisterLocalStateDoublePref(const std::string& path,
                                  double default_value);
void RegisterLocalStateStringPref(const std::string& path,
                                  const std::string& default_value);
void RegisterLocalStateDictPref(const std::string& path,
                                base::DictValue default_value = {});
void RegisterLocalStateListPref(const std::string& path,
                                base::ListValue default_value = {});
void RegisterLocalStateInt64Pref(const std::string& path,
                                 int64_t default_value);
void RegisterLocalStateUint64Pref(const std::string& path,
                                  uint64_t default_value);
void RegisterLocalStateTimePref(const std::string& path,
                                base::Time default_value);
void RegisterLocalStateTimeDeltaPref(const std::string& path,
                                     base::TimeDelta default_value);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_LOCAL_STATE_PREF_REGISTRY_TEST_UTIL_H_
