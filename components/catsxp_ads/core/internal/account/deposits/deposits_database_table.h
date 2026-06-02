/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_DATABASE_TABLE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_DATABASE_TABLE_H_

#include <optional>
#include <string>

#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_table_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads {

struct DepositInfo;

namespace database::table {

using GetDepositsCallback =
    base::OnceCallback<void(bool success, std::optional<DepositInfo> deposit)>;

class Deposits final : public TableInterface {
 public:
  void Save(const DepositInfo& deposit, ResultCallback callback);

  void GetForCreativeInstanceId(const std::string& creative_instance_id,
                                GetDepositsCallback callback) const;

  void PurgeExpired(ResultCallback callback) const;

  // TableInterface:
  void Create(const mojom::DBTransactionInfoPtr& mojom_db_transaction) override;
  void Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               int to_version) override;
};

}  // namespace database::table

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_DATABASE_TABLE_H_
