/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_MAINTENANCE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_MAINTENANCE_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/common/timer/timer.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {
class AdsClient;
class DatabaseManager;
}  // namespace catsxp_ads

namespace catsxp_ads::database {

class Maintenance final : public AdsClientNotifierObserver,
                          public DatabaseManagerObserver {
 public:
  Maintenance();

  Maintenance(const Maintenance&) = delete;
  Maintenance& operator=(const Maintenance&) = delete;

  ~Maintenance() override;

 private:
  void RepeatedlyScheduleAfter(base::TimeDelta after);
  void RepeatedlyScheduleAfterCallback();

  // AdsClientNotifierObserver:
  void OnNotifyPrefDidChange(const std::string& path) override;

  // DatabaseManagerObserver:
  void OnDatabaseIsReady() override;

  Timer timer_;

  base::ScopedObservation<AdsClient, AdsClientNotifierObserver>
      ads_client_observation_{this};

  base::ScopedObservation<DatabaseManager, DatabaseManagerObserver>
      database_manager_observation_{this};

  base::WeakPtrFactory<Maintenance> weak_factory_{this};
};

}  // namespace catsxp_ads::database

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_MAINTENANCE_H_
