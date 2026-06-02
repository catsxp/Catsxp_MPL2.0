/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/common/functional/once_closure_task_queue.h"

#include "base/functional/callback.h"
#include "base/test/mock_callback.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsOnceClosureTaskQueueTest, Add) {
  // Arrange
  OnceClosureTaskQueue task_queue;
  base::MockCallback<base::OnceClosure> task;
  EXPECT_CALL(task, Run()).Times(0);
  task_queue.Add(task.Get());

  // Act & Assert
  EXPECT_FALSE(task_queue.empty());
  EXPECT_TRUE(task_queue.should_queue());
}

TEST(CatsxpAdsOnceClosureTaskQueueTest, AddAndFlush) {
  // Arrange
  OnceClosureTaskQueue task_queue;
  base::MockCallback<base::OnceClosure> task;
  EXPECT_CALL(task, Run());
  task_queue.Add(task.Get());

  // Act & Assert
  task_queue.FlushAndStopQueueing();
  EXPECT_TRUE(task_queue.empty());
  EXPECT_FALSE(task_queue.should_queue());
}

}  // namespace catsxp_ads
