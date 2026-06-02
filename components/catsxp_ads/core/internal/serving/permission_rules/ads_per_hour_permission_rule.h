/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_ADS_PER_HOUR_PERMISSION_RULE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_ADS_PER_HOUR_PERMISSION_RULE_H_

#include <cstddef>

#include "base/containers/span.h"
#include "base/time/time.h"

namespace catsxp_ads {

bool HasAdsPerHourPermission(base::span<const base::Time> history, size_t cap);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_ADS_PER_HOUR_PERMISSION_RULE_H_
