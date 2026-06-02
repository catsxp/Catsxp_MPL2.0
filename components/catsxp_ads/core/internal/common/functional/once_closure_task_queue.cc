/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/common/functional/once_closure_task_queue.h"

#include <utility>

#include "base/check.h"

namespace catsxp_ads {

OnceClosureTaskQueue::OnceClosureTaskQueue() = default;

OnceClosureTaskQueue::~OnceClosureTaskQueue() = default;

void OnceClosureTaskQueue::Add(base::OnceClosure closure) {
  CHECK(should_queue_);

  queue_.push(std::move(closure));
}

void OnceClosureTaskQueue::FlushAndStopQueueing() {
  should_queue_ = false;

  while (!queue_.empty()) {
    std::move(queue_.front()).Run();
    queue_.pop();
  }
}

}  // namespace catsxp_ads
