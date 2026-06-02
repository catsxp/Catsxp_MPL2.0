/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SYNC_SYNC_SERVICE_IMPL_HELPER_H_
#define CATSXP_COMPONENTS_CATSXP_SYNC_SYNC_SERVICE_IMPL_HELPER_H_

#include <string>

#include "base/functional/callback.h"

namespace syncer {
class CatsxpSyncServiceImpl;
class DeviceInfoSyncService;
}  // namespace syncer

namespace catsxp_sync {

// Helper function to break circular dependency between
// //components/sync/service and //component/sync_device_info
void ResetSync(syncer::CatsxpSyncServiceImpl* sync_service_impl,
               syncer::DeviceInfoSyncService* device_info_service,
               base::OnceClosure on_reset_done);

void DeleteDevice(syncer::CatsxpSyncServiceImpl* sync_service_impl,
                  syncer::DeviceInfoSyncService* device_info_service,
                  const std::string& device_guid);

}  // namespace catsxp_sync

#endif  // CATSXP_COMPONENTS_CATSXP_SYNC_SYNC_SERVICE_IMPL_HELPER_H_
