/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_STATEMENT_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_STATEMENT_UTIL_H_

#include <string>

namespace base {
class Time;
}  // namespace base

namespace catsxp_ads::database {

// Convert a time to a SQL value.
std::string TimeToSqlValueAsString(base::Time time);

}  // namespace catsxp_ads::database

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_STATEMENT_UTIL_H_
