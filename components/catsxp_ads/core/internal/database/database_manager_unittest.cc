/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/database/database_manager.h"

#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/internal/database/test/database_manager_observer_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsDatabaseManagerTest : public test::TestBase {
 protected:
  void SetUpMocks() override {
    // Register before `CreateOrOpen` fires in `MockDefaultAdsServiceState` so
    // the observer catches the initial database creation notifications.
    observation_.Observe(&GlobalState::GetInstance()->GetDatabaseManager());

    EXPECT_CALL(observer_mock_, OnWillCreateOrOpenDatabase);
    EXPECT_CALL(observer_mock_, OnDidCreateDatabase);
    EXPECT_CALL(observer_mock_, OnDatabaseIsReady);
    EXPECT_CALL(observer_mock_, OnDidOpenDatabase).Times(0);
    EXPECT_CALL(observer_mock_, OnFailedToCreateOrOpenDatabase).Times(0);
  }

  ::testing::StrictMock<DatabaseManagerObserverMock> observer_mock_;
  base::ScopedObservation<DatabaseManager, DatabaseManagerObserver>
      observation_{&observer_mock_};
};

TEST_F(CatsxpAdsDatabaseManagerTest, NotifiesObserversWhenDatabaseIsCreated) {
  // The observer expectations are set in `SetUpMocks` and verified on mock
  // destruction. Nothing further to assert.
}

}  // namespace catsxp_ads
