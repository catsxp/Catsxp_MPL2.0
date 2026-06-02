/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TIME_TIME_CONSTRAINT_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TIME_TIME_CONSTRAINT_UTIL_H_

#include <cstddef>

#include "base/containers/span.h"
#include "base/time/time.h"

namespace catsxp_ads {

// Check if the `history` of time points respects a certain `time_constraint`
// and a `cap` on the number of elements. Assumes that `history` is in
// chronological order.
bool DoesHistoryRespectRollingTimeConstraint(
    base::span<const base::Time> history,
    base::TimeDelta time_constraint,
    size_t cap);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TIME_TIME_CONSTRAINT_UTIL_H_
