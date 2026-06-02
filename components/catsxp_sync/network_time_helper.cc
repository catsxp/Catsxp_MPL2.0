/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_sync/network_time_helper.h"

#include <utility>

#include "base/logging.h"
#include "base/no_destructor.h"
#include "base/task/single_thread_task_runner.h"
#include "components/network_time/network_time_tracker.h"

namespace catsxp_sync {

// static
NetworkTimeHelper* NetworkTimeHelper::GetInstance() {
  static base::NoDestructor<NetworkTimeHelper> instance;
  return instance.get();
}

NetworkTimeHelper::NetworkTimeHelper() = default;
NetworkTimeHelper::~NetworkTimeHelper() = default;

void NetworkTimeHelper::SetNetworkTimeTracker(
    network_time::NetworkTimeTracker* tracker,
    const scoped_refptr<base::SingleThreadTaskRunner>& ui_task_runner) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  CHECK(tracker->is_initialized());
  network_time_tracker_ = tracker;
  ui_task_runner_ = ui_task_runner;
}

void NetworkTimeHelper::Shutdown() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  network_time_tracker_ = nullptr;
}

void NetworkTimeHelper::GetNetworkTime(GetNetworkTimeCallback cb) {
  if (!network_time_for_test_.is_null()) {
    std::move(cb).Run(network_time_for_test_);
    return;
  }

  // TODO(alexeybarabash): redo it using mojo interface
  // https://github.com/catsxp/catsxp-browser/issues/43738
  ui_task_runner_->PostTask(
      FROM_HERE, base::BindOnce(&NetworkTimeHelper::GetNetworkTimeOnUIThread,
                                base::Unretained(this), std::move(cb)));
}

void NetworkTimeHelper::SetNetworkTimeForTest(const base::Time& time) {
  network_time_for_test_ = time;
}

void NetworkTimeHelper::GetNetworkTimeOnUIThread(GetNetworkTimeCallback cb) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  base::Time time;
  if (!network_time_tracker_ ||
      network_time_tracker_->GetNetworkTime(&time, nullptr) !=
          network_time::NetworkTimeTracker::NETWORK_TIME_AVAILABLE) {
    VLOG(1) << "Network time not available, using local time";
    time = base::Time::Now();
  }
  std::move(cb).Run(time);
}

}  // namespace catsxp_sync
