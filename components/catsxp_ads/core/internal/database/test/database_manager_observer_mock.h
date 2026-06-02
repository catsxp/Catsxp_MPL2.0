/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_TEST_DATABASE_MANAGER_OBSERVER_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_TEST_DATABASE_MANAGER_OBSERVER_MOCK_H_

#include "catsxp/components/catsxp_ads/core/internal/database/database_manager_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class DatabaseManagerObserverMock : public DatabaseManagerObserver {
 public:
  DatabaseManagerObserverMock();

  DatabaseManagerObserverMock(const DatabaseManagerObserverMock&) = delete;
  DatabaseManagerObserverMock& operator=(const DatabaseManagerObserverMock&) =
      delete;

  ~DatabaseManagerObserverMock() override;

  MOCK_METHOD(void, OnWillCreateOrOpenDatabase, ());
  MOCK_METHOD(void, OnDidCreateDatabase, ());
  MOCK_METHOD(void, OnDidOpenDatabase, ());
  MOCK_METHOD(void, OnFailedToCreateOrOpenDatabase, ());
  MOCK_METHOD(void, OnWillMigrateDatabase, (int, int));
  MOCK_METHOD(void, OnDidMigrateDatabase, (int, int));
  MOCK_METHOD(void, OnFailedToMigrateDatabase, (int, int));
  MOCK_METHOD(void, OnDatabaseIsReady, ());
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_TEST_DATABASE_MANAGER_OBSERVER_MOCK_H_
