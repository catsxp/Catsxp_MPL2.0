/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_MANAGER_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_MANAGER_OBSERVER_H_

#include "base/observer_list_types.h"

namespace catsxp_ads {

class DatabaseManagerObserver : public base::CheckedObserver {
 public:
  // Invoked when about to create or open the database.
  virtual void OnWillCreateOrOpenDatabase() {}

  // Invoked when the database was created.
  virtual void OnDidCreateDatabase() {}

  // Invoked when the database was opened.
  virtual void OnDidOpenDatabase() {}

  // Invoked when the database cannot be created or opened.
  virtual void OnFailedToCreateOrOpenDatabase() {}

  // Invoked when about to migrate the database from `from_version` to
  // `to_version`.
  virtual void OnWillMigrateDatabase(int from_version, int to_version) {}

  // Invoked when the database was migrated from `from_version` to `to_version`.
  virtual void OnDidMigrateDatabase(int from_version, int to_version) {}

  // Invoked when the database cannot be migrated from `from_version` to
  // `to_version`.
  virtual void OnFailedToMigrateDatabase(int from_version, int to_version) {}

  // Invoked when the database is ready to be queried.
  virtual void OnDatabaseIsReady() {}
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_MANAGER_OBSERVER_H_
