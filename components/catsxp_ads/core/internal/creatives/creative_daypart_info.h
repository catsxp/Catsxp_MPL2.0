/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_DAYPART_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_DAYPART_INFO_H_

#include <string>

#include "base/containers/flat_set.h"

namespace catsxp_ads {

struct CreativeDaypartInfo final {
  auto operator<=>(const CreativeDaypartInfo&) const = default;

  std::string days_of_week = "0123456";  // Sunday = 0
  int start_minute = 0;                  // 00:00
  int end_minute = 1439;                 // 23:59
};

using CreativeDaypartSet = base::flat_set<CreativeDaypartInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_DAYPART_INFO_H_
