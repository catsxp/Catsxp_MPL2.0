/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CAMPAIGNS_DATABASE_TABLE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CAMPAIGNS_DATABASE_TABLE_H_

#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_table_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::database::table {

class Campaigns final : public TableInterface {
 public:
  Campaigns();

  Campaigns(const Campaigns&) = delete;
  Campaigns& operator=(const Campaigns&) = delete;

  ~Campaigns() override;

  void Insert(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
              const CreativeAdList& creative_ads);

  // TableInterface:
  void Create(const mojom::DBTransactionInfoPtr& mojom_db_transaction) override;
  void Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               int to_version) override;

 private:
  void MigrateToV48(const mojom::DBTransactionInfoPtr& mojom_db_transaction);
  void MigrateToV52(const mojom::DBTransactionInfoPtr& mojom_db_transaction);
};

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CAMPAIGNS_DATABASE_TABLE_H_
