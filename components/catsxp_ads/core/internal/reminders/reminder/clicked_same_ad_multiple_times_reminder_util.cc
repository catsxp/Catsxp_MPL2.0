/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/reminders/reminder/clicked_same_ad_multiple_times_reminder_util.h"

#include <algorithm>
#include <cstddef>

#include "base/check_op.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_notifier_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/reminders/reminders_feature.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

bool ShouldRemindUser() {
  return base::FeatureList::IsEnabled(kRemindersFeature) &&
         kRemindUserIfClickingTheSameAdAfter.Get() > 0;
}

bool DidUserClickTheSameAdMultipleTimes(const std::string& creative_instance_id,
                                        const AdHistoryList& ad_history) {
  const size_t count = std::ranges::count_if(
      ad_history,
      [&creative_instance_id](const AdHistoryItemInfo& ad_history_item) {
        return ad_history_item.creative_instance_id == creative_instance_id &&
               ad_history_item.confirmation_type ==
                   mojom::ConfirmationType::kClicked;
      });

  if (count == 0) {
    return false;
  }

  const size_t remind_user_if_clicking_the_same_ad_after =
      kRemindUserIfClickingTheSameAdAfter.Get();
  CHECK_GT(remind_user_if_clicking_the_same_ad_after, 0U);

  return (count - 1) % remind_user_if_clicking_the_same_ad_after ==
         remind_user_if_clicking_the_same_ad_after - 1;
}

void RemindUserTheyDoNotNeedToClickToEarnRewards() {
  AdsNotifierManager::GetInstance().NotifyRemindUser(
      mojom::ReminderType::kClickedSameAdMultipleTimes);
}

}  // namespace catsxp_ads
