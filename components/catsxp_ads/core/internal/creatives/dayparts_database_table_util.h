/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_DAYPARTS_DATABASE_TABLE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_DAYPARTS_DATABASE_TABLE_UTIL_H_

#include <map>
#include <string>

#include "base/containers/flat_set.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct CreativeDaypartInfo;

namespace database::table {

// Appends SQL actions to insert `dayparts` into the `dayparts` table.
void InsertDayparts(
    const mojom::DBTransactionInfoPtr& mojom_db_transaction,
    const std::map</*campaign_id*/ std::string,
                   base::flat_set<CreativeDaypartInfo>>& dayparts);

}  // namespace database::table

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_DAYPARTS_DATABASE_TABLE_UTIL_H_
