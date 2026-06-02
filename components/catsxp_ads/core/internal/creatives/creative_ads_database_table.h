/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_ADS_DATABASE_TABLE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_ADS_DATABASE_TABLE_H_

#include <string>

#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_table_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::database::table {

using GetCreativeAdCallback =
    base::OnceCallback<void(bool success,
                            const std::string& creative_instance_id,
                            const CreativeAdInfo& creative_ad)>;

class CreativeAds final : public TableInterface {
 public:
  void GetForCreativeInstanceId(const std::string& creative_instance_id,
                                GetCreativeAdCallback callback) const;

  // TableInterface:
  void Create(const mojom::DBTransactionInfoPtr& mojom_db_transaction) override;
  void Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               int to_version) override;

 private:
  void MigrateToV48(const mojom::DBTransactionInfoPtr& mojom_db_transaction);
  void MigrateToV54(const mojom::DBTransactionInfoPtr& mojom_db_transaction);
};

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_ADS_DATABASE_TABLE_H_
