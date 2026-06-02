/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_H_

#include <cstdint>
#include <memory>

#include "base/files/file_path.h"
#include "base/memory/memory_pressure_listener.h"
#include "base/memory/weak_ptr.h"
#include "base/sequence_checker.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "sql/database.h"
#include "sql/meta_table.h"

namespace catsxp_ads {

class Database final : public base::MemoryPressureListener {
 public:
  explicit Database(base::FilePath path);

  Database(const Database&) = delete;
  Database& operator=(const Database&) = delete;

  ~Database() override;

  mojom::DBTransactionResultInfoPtr RunTransaction(
      mojom::DBTransactionInfoPtr mojom_db_transaction,
      uint64_t trace_id);

  void Poison();

 private:
  mojom::DBTransactionResultInfo::StatusCode RunActions(
      const mojom::DBTransactionInfoPtr& mojom_db_transaction,
      const mojom::DBTransactionResultInfoPtr& mojom_db_transaction_result,
      uint64_t trace_id);

  mojom::DBTransactionResultInfo::StatusCode MaybeRaze(
      const mojom::DBTransactionInfoPtr& mojom_db_transaction,
      uint64_t trace_id);

  bool InitializeMetaTable();

  bool ShouldCreateTables();
  mojom::DBTransactionResultInfo::StatusCode Initialize(
      const mojom::DBTransactionResultInfoPtr& mojom_db_transaction_result);

  mojom::DBTransactionResultInfo::StatusCode Execute(
      const mojom::DBActionInfoPtr& mojom_db_action);
  mojom::DBTransactionResultInfo::StatusCode ExecuteWithBindings(
      const mojom::DBActionInfoPtr& mojom_db_action);
  mojom::DBTransactionResultInfo::StatusCode ExecuteQueryWithBindings(
      const mojom::DBActionInfoPtr& mojom_db_action,
      const mojom::DBTransactionResultInfoPtr& mojom_db_transaction_result);

  mojom::DBTransactionResultInfo::StatusCode Migrate();

  mojom::DBTransactionResultInfo::StatusCode MaybeVacuum(
      const mojom::DBTransactionInfoPtr& mojom_db_transaction,
      uint64_t trace_id);

  void ErrorCallback(int error, sql::Statement* statement);

  // base::MemoryPressureListener:
  void OnMemoryPressure(base::MemoryPressureLevel level) override;

  const base::FilePath db_path_;
  sql::Database db_;
  sql::MetaTable meta_table_;

  bool is_initialized_ = false;

  std::unique_ptr<base::AsyncMemoryPressureListenerRegistration>
      memory_pressure_listener_registration_;

  SEQUENCE_CHECKER(sequence_checker_);

  base::WeakPtrFactory<Database> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_H_
