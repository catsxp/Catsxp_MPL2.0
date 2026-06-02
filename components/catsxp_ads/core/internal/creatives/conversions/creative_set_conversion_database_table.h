/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_DATABASE_TABLE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_DATABASE_TABLE_H_

#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"
#include "catsxp/components/catsxp_ads/core/internal/database/database_table_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads::database::table {

using GetCreativeSetConversionsCallback = base::OnceCallback<void(
    bool success,
    const CreativeSetConversionList& creative_set_conversions)>;

class CreativeSetConversions final : public TableInterface {
 public:
  void Save(const CreativeSetConversionList& creative_set_conversions,
            ResultCallback callback);

  void GetUnexpired(GetCreativeSetConversionsCallback callback) const;
  void GetActive(GetCreativeSetConversionsCallback callback) const;

  void PurgeExpired(ResultCallback callback) const;

  // TableInterface:
  void Create(const mojom::DBTransactionInfoPtr& mojom_db_transaction) override;
  void Migrate(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
               int to_version) override;

};

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_DATABASE_TABLE_H_
