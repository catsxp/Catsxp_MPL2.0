/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_DATABASE_TABLE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_DATABASE_TABLE_UTIL_H_

#include <map>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposit_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_deposit_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::database::table {

DepositInfo DepositFromMojomRow(const mojom::DBRowInfoPtr& mojom_db_row);

// Appends SQL actions to insert `deposits` into the `deposits` table.
void InsertDeposits(const mojom::DBTransactionInfoPtr& mojom_db_transaction,
                    const std::map</*creative_instance_id*/ std::string,
                                   CreativeDepositInfo>& deposits);

}  // namespace catsxp_ads::database::table

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_DATABASE_TABLE_UTIL_H_
