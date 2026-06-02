/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_SYNC_CATSXP_SYNC_SERVICE_IMPL_DELEGATE_H_
#define CATSXP_BROWSER_SYNC_CATSXP_SYNC_SERVICE_IMPL_DELEGATE_H_

#include <utility>

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "catsxp/components/sync/service/sync_service_impl_delegate.h"
#include "components/sync_device_info/device_info_tracker.h"

namespace history {
class HistoryService;
}  // namespace history

namespace syncer {

class CatsxpSyncServiceImpl;
class DeviceInfoSyncService;
class DeviceInfoTracker;
class LocalDeviceInfoProvider;

// Helper class to prevent pass of profile pointer into CatsxpSyncServiceImpl
// and to keep DeviceInfoSyncService
class CatsxpSyncServiceImplDelegate
    : public SyncServiceImplDelegate,
      public syncer::DeviceInfoTracker::Observer {
 public:
  explicit CatsxpSyncServiceImplDelegate(
      DeviceInfoSyncService* device_info_sync_service,
      history::HistoryService* history_service);
  ~CatsxpSyncServiceImplDelegate() override;

  void SuspendDeviceObserverForOwnReset() override;
  void ResumeDeviceObserver() override;

  void SetLocalDeviceAppearedCallback(
      base::OnceCallback<void()> local_device_appeared_callback) override;

  void GetKnownToSyncHistoryCount(
      base::OnceCallback<void(std::pair<bool, int>)> callback) override;

 private:
  // syncer::DeviceInfoTracker::Observer:
  void OnDeviceInfoChange() override;

  void OnSelfDeviceInfoDeleted(void);

  void RecordP3ASyncStatus();

  raw_ptr<syncer::DeviceInfoTracker> device_info_tracker_ = nullptr;
  raw_ptr<syncer::LocalDeviceInfoProvider> local_device_info_provider_ =
      nullptr;
  base::ScopedObservation<syncer::DeviceInfoTracker,
                          syncer::DeviceInfoTracker::Observer>
      device_info_observer_{this};

  raw_ptr<DeviceInfoSyncService> device_info_sync_service_ = nullptr;
  raw_ptr<history::HistoryService> history_service_ = nullptr;

  bool is_google_sync_;
  // This is triggered once after SetLocalDeviceAppearedCallback
  // when the local device first appears in the changed synced devices list
  base::OnceCallback<void()> local_device_appeared_callback_;

  base::WeakPtrFactory<CatsxpSyncServiceImplDelegate> weak_ptr_factory_;

  CatsxpSyncServiceImplDelegate(const CatsxpSyncServiceImplDelegate&) = delete;
  CatsxpSyncServiceImplDelegate& operator=(const CatsxpSyncServiceImplDelegate&) =
      delete;
};

}  // namespace syncer

#endif  // CATSXP_BROWSER_SYNC_CATSXP_SYNC_SERVICE_IMPL_DELEGATE_H_
