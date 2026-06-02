/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/time/time_constraint_util.h"

#include "base/containers/adapters.h"
#include "base/containers/span.h"
#include "base/time/time.h"

namespace catsxp_ads {

bool DoesHistoryRespectRollingTimeConstraint(
    base::span<const base::Time> history,
    base::TimeDelta time_constraint,
    size_t cap) {
  if (cap == 0) {
    // If the cap is set to 0, then there is no time constraint.
    return true;
  }

  const base::Time threshold = base::Time::Now() - time_constraint;

  for (const auto& time : base::Reversed(history)) {
    if (time <= threshold) {
      // If the time point is less than or equal to the threshold, the cap has
      // not been reached.
      break;
    }

    --cap;
    if (cap == 0) {
      // If the cap is hit, the limit has been reached.
      return false;
    }
  }

  return true;
}

}  // namespace catsxp_ads
