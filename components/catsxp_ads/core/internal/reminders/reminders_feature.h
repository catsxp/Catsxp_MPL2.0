/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_REMINDERS_REMINDERS_FEATURE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_REMINDERS_REMINDERS_FEATURE_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace catsxp_ads {

BASE_DECLARE_FEATURE(kRemindersFeature);

inline constexpr base::FeatureParam<size_t> kRemindUserIfClickingTheSameAdAfter{
    &kRemindersFeature, "remind_user_if_clicking_the_same_ad_after", 3};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_REMINDERS_REMINDERS_FEATURE_H_
