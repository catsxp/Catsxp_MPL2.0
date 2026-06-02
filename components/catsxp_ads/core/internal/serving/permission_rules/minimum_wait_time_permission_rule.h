/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_MINIMUM_WAIT_TIME_PERMISSION_RULE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_MINIMUM_WAIT_TIME_PERMISSION_RULE_H_

#include "base/containers/span.h"
#include "base/time/time.h"

namespace catsxp_ads {

bool HasMinimumWaitTimePermission(base::span<const base::Time> history,
                                  base::TimeDelta time_constraint);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_PERMISSION_RULES_MINIMUM_WAIT_TIME_PERMISSION_RULE_H_
