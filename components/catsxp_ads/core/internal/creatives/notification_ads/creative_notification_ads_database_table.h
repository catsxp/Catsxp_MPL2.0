/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_CREATIVE_NOTIFICATION_ADS_DATABASE_TABLE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_CREATIVE_NOTIFICATION_ADS_DATABASE_TABLE_H_

#include "base/check_op.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/campaigns_database_table.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/notification_ads/creative_notification_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_table_interface.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads::database::table {

using GetCreativeNotificationAdsCallback =
    base::OnceCallback<void(bool success,
                            const SegmentList& segments,
                            CreativeNotificationAdList creative_ads)>;

class CreativeNotificationAds final : public TableInterface {
 public:
  CreativeNotificationAds();

  CreativeNotificationAds(const CreativeNotificationAds&) = delete;
  CreativeNotificationAds& operator=(const CreativeNotificationAds&) = delete;

  ~CreativeNotificationAds() override;

  void Save(const CreativeNotificationAdList& creative_ads,
            ResultCallback callback);

  void GetForSegments(const SegmentList& segments,
                      GetCreativeNotificationAdsCallback callback) const;

  void GetForActiveCampaigns(GetCreativeNotificationAdsCallback callback) const;

  void SetBatchSize(int batch_size) {
    CHECK_GT(batch_size, 0);

    batch_size_ = batch_size;
  }

  // TableInterface:
  void Create(const mojom::DBTransactionInfoPtr& mojom_db_transaction) override;
  void Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               int to_version) override;

 private:
  void MigrateToV48(const mojom::DBTransactionInfoPtr& mojom_db_transaction);

  int batch_size_;

  Campaigns campaigns_database_table_;
};

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NOTIFICATION_ADS_CREATIVE_NOTIFICATION_ADS_DATABASE_TABLE_H_
