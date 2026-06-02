/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_COMMON_FUNCTIONAL_ONCE_CLOSURE_TASK_QUEUE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_COMMON_FUNCTIONAL_ONCE_CLOSURE_TASK_QUEUE_H_

#include "base/containers/queue.h"
#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

class OnceClosureTaskQueue final {
 public:
  OnceClosureTaskQueue();

  OnceClosureTaskQueue(const OnceClosureTaskQueue&) = delete;
  OnceClosureTaskQueue& operator=(const OnceClosureTaskQueue&) = delete;

  ~OnceClosureTaskQueue();

  void Add(base::OnceClosure closure);
  void FlushAndStopQueueing();

  bool should_queue() const { return should_queue_; }

  bool empty() const { return queue_.empty(); }

 private:
  bool should_queue_ = true;
  base::queue<base::OnceClosure> queue_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_COMMON_FUNCTIONAL_ONCE_CLOSURE_TASK_QUEUE_H_
