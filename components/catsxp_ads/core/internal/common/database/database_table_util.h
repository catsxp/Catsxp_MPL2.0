/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_TABLE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_TABLE_UTIL_H_

#include <string>
#include <vector>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::database {

void CreateTableIndex(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                      const std::string& table_name,
                      const std::vector<std::string>& columns);

void DropTableIndex(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                    const std::string& index_name);

void DropTable(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               const std::string& table_name);

void DeleteTable(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                 const std::string& table_name);

void CopyTableColumns(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                      const std::string& from,
                      const std::string& to,
                      const std::vector<std::string>& from_columns,
                      const std::vector<std::string>& to_columns,
                      bool should_drop);

void CopyTableColumns(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                      const std::string& from,
                      const std::string& to,
                      const std::vector<std::string>& columns,
                      bool should_drop);

void RenameTable(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                 const std::string& from,
                 const std::string& to);

}  // namespace catsxp_ads::database

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_TABLE_UTIL_H_
