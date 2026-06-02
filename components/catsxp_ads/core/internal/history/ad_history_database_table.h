/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_DATABASE_TABLE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_DATABASE_TABLE_H_

#include <string>

#include "base/check_op.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_table_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_callback.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

namespace catsxp_ads::database::table {

class AdHistory final : public TableInterface {
 public:
  AdHistory();

  void Save(const AdHistoryList& ad_history, ResultCallback callback) const;

  void GetForDateRange(base::Time from_time,
                       base::Time to_time,
                       GetAdHistoryCallback callback) const;
  void GetHighestRankedPlacementsForDateRange(
      base::Time from_time,
      base::Time to_time,
      GetAdHistoryCallback callback) const;
  void GetForCreativeInstanceId(const std::string& creative_instance_id,
                                GetAdHistoryCallback callback) const;

  void PurgeExpired(ResultCallback callback) const;

  void SetBatchSize(int batch_size) {
    CHECK_GT(batch_size, 0);

    batch_size_ = batch_size;
  }

  // TableInterface:
  void Create(const mojom::DBTransactionInfoPtr& mojom_db_transaction) override;
  void Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               int to_version) override;

 private:
  int batch_size_;
};

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_DATABASE_TABLE_H_
