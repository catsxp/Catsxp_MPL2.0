/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_PAGE_TRANSITION_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_PAGE_TRANSITION_UTIL_H_

#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/user_activity_event_types.h"
#include "ui/base/page_transition_types.h"

namespace catsxp_ads {

std::optional<UserActivityEventType> ToUserActivityEventType(
    ui::PageTransition page_transition);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_PAGE_TRANSITION_UTIL_H_
