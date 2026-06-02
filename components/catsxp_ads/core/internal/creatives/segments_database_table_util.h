/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_SEGMENTS_DATABASE_TABLE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_SEGMENTS_DATABASE_TABLE_UTIL_H_

#include <map>
#include <string>

#include "base/containers/flat_set.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::database::table {

// Appends SQL actions to insert `segments` into the `segments` table.
void InsertSegments(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                    const std::map</*creative_set_id*/ std::string,
                                   base::flat_set<std::string>>& segments);

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_SEGMENTS_DATABASE_TABLE_UTIL_H_
