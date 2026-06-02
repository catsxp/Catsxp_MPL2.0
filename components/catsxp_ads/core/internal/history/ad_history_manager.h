/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_MANAGER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_MANAGER_H_

#include <optional>
#include <string>

#include "base/observer_list.h"
#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_callback.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

namespace base {
class Time;
}  // namespace base

namespace catsxp_ads {

struct AdInfo;
struct NewTabPageAdInfo;
struct NotificationAdInfo;
struct SearchResultAdInfo;

class AdHistoryManager final {
 public:
  AdHistoryManager();

  AdHistoryManager(const AdHistoryManager&) = delete;
  AdHistoryManager& operator=(const AdHistoryManager&) = delete;

  ~AdHistoryManager();

  static AdHistoryManager& GetInstance();

  void AddObserver(AdHistoryManagerObserver* observer);
  void RemoveObserver(AdHistoryManagerObserver* observer);

  static void Get(base::Time from_time,
                  base::Time to_time,
                  GetAdHistoryCallback callback);
  static void GetForUI(base::Time from_time,
                       base::Time to_time,
                       GetAdHistoryForUICallback callback);

  void Add(const NewTabPageAdInfo& ad,
           mojom::ConfirmationType mojom_confirmation_type);
  void Add(const NotificationAdInfo& ad,
           mojom::ConfirmationType mojom_confirmation_type);
  void Add(const SearchResultAdInfo& ad,
           mojom::ConfirmationType mojom_confirmation_type);

 private:
  void MaybeAdd(const AdInfo& ad,
                mojom::ConfirmationType mojom_confirmation_type,
                const std::string& title,
                const std::string& description);

  static void GetForUICallback(GetAdHistoryForUICallback callback,
                               std::optional<AdHistoryList> ad_history);

  void NotifyDidAddAdHistoryItem(const AdHistoryItemInfo& ad_history_item);

  base::ObserverList<AdHistoryManagerObserver> observers_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_MANAGER_H_
