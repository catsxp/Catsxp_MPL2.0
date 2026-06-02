/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_ADS_DATABASE_TABLE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_ADS_DATABASE_TABLE_H_

#include <string>

#include "base/check_op.h"
#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/campaigns_database_table.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_table_interface.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads::database::table {

using GetCreativeNewTabPageAdCallback =
    base::OnceCallback<void(bool success,
                            const std::string& creative_instance_id,
                            const CreativeNewTabPageAdInfo& creative_ad)>;

using GetCreativeNewTabPageAdsCallback =
    base::OnceCallback<void(bool success,
                            const SegmentList& segments,
                            CreativeNewTabPageAdList creative_ads)>;

class CreativeNewTabPageAds final : public TableInterface {
 public:
  CreativeNewTabPageAds();

  CreativeNewTabPageAds(const CreativeNewTabPageAds&) = delete;
  CreativeNewTabPageAds& operator=(const CreativeNewTabPageAds&) = delete;

  ~CreativeNewTabPageAds() override;

  void Save(const CreativeNewTabPageAdList& creative_ads,
            ResultCallback callback);

  void GetForCreativeInstanceId(const std::string& creative_instance_id,
                                GetCreativeNewTabPageAdCallback callback) const;

  void GetForSegments(const SegmentList& segments,
                      GetCreativeNewTabPageAdsCallback callback) const;

  void GetForActiveCampaigns(GetCreativeNewTabPageAdsCallback callback) const;

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
  void MigrateToV49(const mojom::DBTransactionInfoPtr& mojom_db_transaction);

  int batch_size_;

  Campaigns campaigns_database_table_;
};

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_NEW_TAB_PAGE_ADS_CREATIVE_NEW_TAB_PAGE_ADS_DATABASE_TABLE_H_
