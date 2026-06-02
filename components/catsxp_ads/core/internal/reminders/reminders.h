/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_REMINDERS_REMINDERS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_REMINDERS_REMINDERS_H_

#include <optional>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "base/timer/timer.h"
#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

namespace catsxp_ads {

class AdHistoryManager;

class Reminders final : public AdHistoryManagerObserver {
 public:
  Reminders();

  Reminders(const Reminders&) = delete;
  Reminders& operator=(const Reminders&) = delete;

  ~Reminders() override;

 private:
  void MaybeShowReminders(const AdHistoryItemInfo& ad_history_item);

  bool CanShowUserClickTheSameAdMultipleTimesReminder(
      const AdHistoryItemInfo& ad_history_item);
  void MaybeShowUserClickTheSameAdMultipleTimesReminderAfterDelay(
      const AdHistoryItemInfo& ad_history_item);
  void MaybeShowUserClickTheSameAdMultipleTimesReminder(
      const AdHistoryItemInfo& ad_history_item);
  void MaybeShowUserClickTheSameAdMultipleTimesReminderCallback(
      const std::string& creative_instance_id,
      std::optional<AdHistoryList> ad_history);

  // AdHistoryManagerObserver:
  void OnDidAddAdHistoryItem(const AdHistoryItemInfo& ad_history_item) override;

  base::OneShotTimer timer_;

  base::ScopedObservation<AdHistoryManager, AdHistoryManagerObserver>
      ad_history_manager_observation_{this};

  base::WeakPtrFactory<Reminders> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_REMINDERS_REMINDERS_H_
