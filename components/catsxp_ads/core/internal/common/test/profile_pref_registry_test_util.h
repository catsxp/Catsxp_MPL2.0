/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_PROFILE_PREF_REGISTRY_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_PROFILE_PREF_REGISTRY_TEST_UTIL_H_

#include <cstdint>
#include <string>

#include "base/values.h"

namespace base {
class Time;
class TimeDelta;
}  // namespace base

namespace catsxp_ads::test {

void RegisterProfilePref(const std::string& path, base::Value default_value);
void RegisterProfileBooleanPref(const std::string& path, bool default_value);
void RegisterProfileIntegerPref(const std::string& path, int default_value);
void RegisterProfileDoublePref(const std::string& path, double default_value);
void RegisterProfileStringPref(const std::string& path,
                               const std::string& default_value);
void RegisterProfileDictPref(const std::string& path,
                             base::DictValue default_value = {});
void RegisterProfileListPref(const std::string& path,
                             base::ListValue default_value = {});
void RegisterProfileInt64Pref(const std::string& path, int64_t default_value);
void RegisterProfileUint64Pref(const std::string& path, uint64_t default_value);
void RegisterProfileTimePref(const std::string& path, base::Time default_value);
void RegisterProfileTimeDeltaPref(const std::string& path,
                                  base::TimeDelta default_value);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_PROFILE_PREF_REGISTRY_TEST_UTIL_H_
