/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SYNC_NETWORK_TIME_HELPER_H_
#define CATSXP_COMPONENTS_CATSXP_SYNC_NETWORK_TIME_HELPER_H_

#include "base/functional/callback.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/scoped_refptr.h"
#include "base/memory/weak_ptr.h"
#include "base/sequence_checker.h"
#include "base/time/time.h"

namespace base {
template <typename T>
class NoDestructor;
class SingleThreadTaskRunner;
}  // namespace base

namespace network_time {
class NetworkTimeTracker;
}  // namespace network_time

namespace catsxp_sync {

class NetworkTimeHelper {
 public:
  using GetNetworkTimeCallback = base::OnceCallback<void(const base::Time&)>;

  static NetworkTimeHelper* GetInstance();

  NetworkTimeHelper();
  NetworkTimeHelper(const NetworkTimeHelper&) = delete;
  NetworkTimeHelper& operator=(const NetworkTimeHelper&) = delete;
  virtual ~NetworkTimeHelper();

  void SetNetworkTimeTracker(
      network_time::NetworkTimeTracker* tracker,
      const scoped_refptr<base::SingleThreadTaskRunner>& ui_task_runner);

  void Shutdown();

  void GetNetworkTime(GetNetworkTimeCallback cb);

  void SetNetworkTimeForTest(const base::Time& time);

 private:
  friend base::NoDestructor<NetworkTimeHelper>;

  void GetNetworkTimeOnUIThread(GetNetworkTimeCallback cb);

  scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner_;
  base::Time network_time_for_test_;

  SEQUENCE_CHECKER(sequence_checker_);

  // Not owned
  raw_ptr<network_time::NetworkTimeTracker, DanglingUntriaged>
      network_time_tracker_ = nullptr;
};

}  // namespace catsxp_sync

#endif  // CATSXP_COMPONENTS_CATSXP_SYNC_NETWORK_TIME_HELPER_H_
