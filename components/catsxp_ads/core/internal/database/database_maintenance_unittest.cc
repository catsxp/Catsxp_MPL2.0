/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/database/database_maintenance.h"

#include <memory>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::database {

class CatsxpAdsDatabaseMaintenanceTest : public test::TestBase {
 protected:
  void SetUpMocks() override {
    // Must be created here so it registers with DatabaseManager before
    // OnDatabaseIsReady fires during TestBase::SetUp.
    maintenance_ = std::make_unique<Maintenance>();
  }

  std::unique_ptr<Maintenance> maintenance_;
};

TEST_F(CatsxpAdsDatabaseMaintenanceTest, SchedulesInitialMaintenance) {
  // Assert
  EXPECT_EQ(base::Minutes(1), NextPendingTaskDelay());
}

TEST_F(CatsxpAdsDatabaseMaintenanceTest, ReschedulesAfterRecurringInterval) {
  // Act
  FastForwardClockToNextPendingTask();

  // Assert
  EXPECT_EQ(base::Days(1), NextPendingTaskDelay());
}

}  // namespace catsxp_ads::database
