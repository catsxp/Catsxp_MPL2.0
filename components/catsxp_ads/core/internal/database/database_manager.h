/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_MANAGER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_MANAGER_H_

#include "base/memory/scoped_refptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/threading/sequence_bound.h"
#include "catsxp/components/catsxp_ads/core/internal/common/database/database_transaction_callback.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace base {
class FilePath;
class SequencedTaskRunner;
}  // namespace base

namespace catsxp_ads {

class Database;

class DatabaseManager final {
 public:
  explicit DatabaseManager(const base::FilePath& path);

  DatabaseManager(const DatabaseManager&) = delete;
  DatabaseManager& operator=(const DatabaseManager&) = delete;

  ~DatabaseManager();

  static DatabaseManager& GetInstance();

  void AddObserver(DatabaseManagerObserver* observer);
  void RemoveObserver(DatabaseManagerObserver* observer);

  // Create or open the database.
  void CreateOrOpen(ResultCallback callback);

  // Run a database transaction. The callback takes one argument -
  // `mojom::DBTransactionResultInfoPtr` containing the info of the transaction.
  void RunTransaction(mojom::DBTransactionInfoPtr mojom_db_transaction,
                      RunDBTransactionCallback callback,
                      uint64_t trace_id);

  // Shutdowns the database.
  void Shutdown(ResultCallback callback);

 private:
  void CreateOrOpenCallback(
      ResultCallback callback,
      mojom::DBTransactionResultInfoPtr mojom_db_transaction_result);
  void OnRunTransactionCallback(
      RunDBTransactionCallback callback,
      mojom::DBTransactionResultInfoPtr mojom_db_transaction_result);
  void OnShutdownCallback(ResultCallback callback, bool success);

  // Create the database from scratch.
  void Create(ResultCallback callback);
  void CreateCallback(ResultCallback callback, bool success);

  // Raze the database and create it from scratch.
  void RazeAndCreate(int from_version, ResultCallback callback);
  void RazeAndCreateCallback(ResultCallback callback,
                             int from_version,
                             bool success);

  // Migrate the database from `from_version` to the current version.
  void MaybeMigrate(int from_version, ResultCallback callback);
  void MigrateFromVersionCallback(int from_version,
                                  ResultCallback callback,
                                  bool success);

  void NotifyWillCreateOrOpenDatabase();
  void NotifyDidCreateDatabase();
  void NotifyDidOpenDatabase();
  void NotifyFailedToCreateOrOpenDatabase();
  void NotifyWillMigrateDatabase(int from_version, int to_version);
  void NotifyDidMigrateDatabase(int from_version, int to_version);
  void NotifyFailedToMigrateDatabase(int from_version, int to_version);
  void NotifyDatabaseIsReady();

  const scoped_refptr<base::SequencedTaskRunner> database_task_runner_;
  base::SequenceBound<Database> database_;

  base::ObserverList<DatabaseManagerObserver> observers_;

  base::WeakPtrFactory<DatabaseManager> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_MANAGER_H_
