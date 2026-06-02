/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_REMINDERS_REMINDERS_CONSTANTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_REMINDERS_REMINDERS_CONSTANTS_H_

#include "base/time/time.h"

namespace catsxp_ads {

inline constexpr base::TimeDelta kMaybeShowReminderAfter =
    base::Milliseconds(100);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_REMINDERS_REMINDERS_CONSTANTS_H_
