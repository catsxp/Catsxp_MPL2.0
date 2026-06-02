/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

// Serializes and deserializes a ConditionMatcherMap for storage in a single
// database column string.

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONDITION_MATCHERS_DATABASE_TABLE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONDITION_MATCHERS_DATABASE_TABLE_UTIL_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/condition_matcher_util.h"

namespace catsxp_ads::database::table {

std::string ConditionMatchersToString(
    const ConditionMatcherMap& condition_matchers);

ConditionMatcherMap StringToConditionMatchers(const std::string& value);

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONDITION_MATCHERS_DATABASE_TABLE_UTIL_H_
