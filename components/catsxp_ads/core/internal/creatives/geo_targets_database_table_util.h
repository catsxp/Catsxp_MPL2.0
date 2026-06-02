/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_GEO_TARGETS_DATABASE_TABLE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_GEO_TARGETS_DATABASE_TABLE_UTIL_H_

#include <map>
#include <string>

#include "base/containers/flat_set.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::database::table {

// Appends SQL actions to insert `geo_targets` into the `geo_targets` table.
void InsertGeoTargets(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                      const std::map</*campaign_id*/ std::string,
                                     base::flat_set<std::string>>& geo_targets);

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_GEO_TARGETS_DATABASE_TABLE_UTIL_H_
