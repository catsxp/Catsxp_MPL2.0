/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_REMINDERS_REMINDER_CLICKED_SAME_AD_MULTIPLE_TIMES_REMINDER_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_REMINDERS_REMINDER_CLICKED_SAME_AD_MULTIPLE_TIMES_REMINDER_UTIL_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

namespace catsxp_ads {

bool ShouldRemindUser();

bool DidUserClickTheSameAdMultipleTimes(const std::string& creative_instance_id,
                                        const AdHistoryList& ad_history);

void RemindUserTheyDoNotNeedToClickToEarnRewards();

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_REMINDERS_REMINDER_CLICKED_SAME_AD_MULTIPLE_TIMES_REMINDER_UTIL_H_
