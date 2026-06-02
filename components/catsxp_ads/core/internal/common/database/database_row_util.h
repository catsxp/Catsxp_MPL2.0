/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_ROW_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_ROW_UTIL_H_

#include "base/containers/span.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "sql/statement.h"

namespace catsxp_ads::database {

[[nodiscard]] mojom::DBRowInfoPtr CreateRow(
    sql::Statement* statement,
    base::span<const mojom::DBBindColumnType> mojom_db_bind_column_types);

}  // namespace catsxp_ads::database

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_ROW_UTIL_H_
