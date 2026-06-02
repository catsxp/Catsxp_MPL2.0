/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_SYNC_CATSXP_SYNC_ALERTS_SERVICE_H_
#define CATSXP_BROWSER_SYNC_CATSXP_SYNC_ALERTS_SERVICE_H_

#include "base/memory/raw_ptr.h"
#include "base/scoped_multi_source_observation.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/sync/service/sync_service.h"
#include "components/sync/service/sync_service_observer.h"

class Profile;

namespace syncer {
class SyncService;
class SyncServiceObserver;
}  // namespace syncer

class CatsxpSyncAlertsService : public KeyedService,
                               public syncer::SyncServiceObserver {
 public:
  explicit CatsxpSyncAlertsService(Profile* profile);
  CatsxpSyncAlertsService(const CatsxpSyncAlertsService&) = delete;
  CatsxpSyncAlertsService& operator=(const CatsxpSyncAlertsService&) = delete;
  ~CatsxpSyncAlertsService() override;

 private:
  // syncer::SyncServiceObserver implementation.
  void OnStateChanged(syncer::SyncService* service) override;
  void OnSyncShutdown(syncer::SyncService* sync) override;

  void ShowInfobar();
  void ShowSyncCannotRunInfobar();

  raw_ptr<Profile> profile_ = nullptr;
  base::ScopedMultiSourceObservation<syncer::SyncService,
                                     syncer::SyncServiceObserver>
      sync_service_observer_{this};
  base::WeakPtrFactory<CatsxpSyncAlertsService> weak_ptr_factory_{this};
};

#endif  // CATSXP_BROWSER_SYNC_CATSXP_SYNC_ALERTS_SERVICE_H_
