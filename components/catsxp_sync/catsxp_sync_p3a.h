/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SYNC_CATSXP_SYNC_P3A_H_
#define CATSXP_COMPONENTS_CATSXP_SYNC_CATSXP_SYNC_P3A_H_

#include "components/sync/base/user_selectable_type.h"

namespace catsxp_sync {
namespace p3a {

// TODO(alexeybarabash): move here also "Catsxp.Sync.Status.2" and
// "Catsxp.Sync.ProgressTokenEverReset"
inline constexpr char kEnabledTypesHistogramName[] = "Catsxp.Sync.EnabledTypes";
// Improved version of metric which includes count of synced History objects
inline constexpr char kSyncedObjectsCountHistogramNameV2[] =
    "Catsxp.Sync.SyncedObjectsCount.2";
inline constexpr char kSyncJoinTypeHistogramName[] = "Catsxp.Sync.JoinType";

enum class EnabledTypesAnswer {
  kEmptyOrBookmarksOnly = 0,
  kBookmarksAndHistory = 1,
  kMoreThanBookmarksAndHistory = 2,
  kAllTypes = 3,
  kMaxValue = kAllTypes
};

enum class SyncJoinType {
  kChainCreated = 1,
  kChainJoined = 2,
  kMaxValue = kChainJoined
};

void RecordEnabledTypes(bool sync_everything_enabled,
                        const syncer::UserSelectableTypeSet& selected_types);
void RecordSyncedObjectsCount(int total_entities);

// Monitors sync code generation and setting events in order
// to report the `Catsxp.Sync.JoinType` metric.
class SyncCodeMonitor {
 public:
  SyncCodeMonitor() = default;
  ~SyncCodeMonitor() = default;

  SyncCodeMonitor(const SyncCodeMonitor&) = delete;
  SyncCodeMonitor& operator=(const SyncCodeMonitor&) = delete;

  void RecordCodeGenerated();
  void RecordCodeSet();

 private:
  bool code_generated_ = false;
};

}  // namespace p3a
}  // namespace catsxp_sync

#endif  // CATSXP_COMPONENTS_CATSXP_SYNC_CATSXP_SYNC_P3A_H_
