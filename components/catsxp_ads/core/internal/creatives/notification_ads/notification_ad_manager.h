/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_NOTIFICATION_AD_MANAGER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_NOTIFICATION_AD_MANAGER_H_

#include <optional>
#include <string>

#include "base/containers/circular_deque.h"

namespace catsxp_ads {

struct NotificationAdInfo;

class NotificationAdManager final {
 public:
  NotificationAdManager();

  NotificationAdManager(const NotificationAdManager&) = delete;
  NotificationAdManager& operator=(const NotificationAdManager&) = delete;

  ~NotificationAdManager();

  static NotificationAdManager& GetInstance();

  std::optional<NotificationAdInfo> MaybeGetForPlacementId(
      const std::string& placement_id) const;

  void Add(const NotificationAdInfo& ad);

  void Remove(const std::string& placement_id, bool should_close);
  void RemoveAll(bool should_close);

  bool Exists(const std::string& placement_id) const;

 private:
  void Initialize();

  void MaybeRemoveAll();

  base::circular_deque<NotificationAdInfo> ads_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_NOTIFICATION_AD_MANAGER_H_
