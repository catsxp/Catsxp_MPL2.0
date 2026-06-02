/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_LOGGING_UTIL_INTERNAL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_LOGGING_UTIL_INTERNAL_H_

#include <string>

namespace catsxp_ads {

void Log(const char* file,
         int line,
         int verbose_level,
         const std::string& message);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_LOGGING_UTIL_INTERNAL_H_
