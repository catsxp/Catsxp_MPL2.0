/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_TABLE_INTERFACE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_TABLE_INTERFACE_H_

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::database {

class TableInterface {
 public:
  // Invoked to create a table in the database. This ensures that the necessary
  // structure is in place for storing and managing data.
  virtual void Create(
      const mojom::DBTransactionInfoPtr& mojom_db_transaction) = 0;

  // Invoked to migrate the database table to the given version.
  virtual void Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                       int to_version);

 protected:
  virtual ~TableInterface() = default;
};

}  // namespace catsxp_ads::database

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DATABASE_DATABASE_TABLE_INTERFACE_H_
