/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/dayparts_database_table_util.h"

#include <cstddef>
#include <cstdint>
#include <utility>

#include "base/check.h"
#include "base/containers/flat_set.h"
#include "base/strings/string_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/database/database_column_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/database/database_table_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_daypart_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::database::table {

namespace {

constexpr char kTableName[] = "dayparts";

size_t BindColumns(
    const mojom::DBActionInfoPtr& mojom_db_action,
    const std::map</*campaign_id*/ std::string,
                   base::flat_set<CreativeDaypartInfo>>& dayparts) {
  CHECK(mojom_db_action);
  CHECK(!dayparts.empty());

  size_t row_count = 0;

  int32_t index = 0;
  for (const auto& [campaign_id, dayparts_set] : dayparts) {
    for (const auto& daypart : dayparts_set) {
      BindColumnString(mojom_db_action, index++, campaign_id);
      BindColumnString(mojom_db_action, index++, daypart.days_of_week);
      BindColumnInt(mojom_db_action, index++, daypart.start_minute);
      BindColumnInt(mojom_db_action, index++, daypart.end_minute);

      ++row_count;
    }
  }

  return row_count;
}

std::string BuildInsertSql(
    const mojom::DBActionInfoPtr& mojom_db_action,
    const std::map</*campaign_id*/ std::string,
                   base::flat_set<CreativeDaypartInfo>>& dayparts) {
  CHECK(mojom_db_action);
  CHECK(!dayparts.empty());

  const size_t row_count = BindColumns(mojom_db_action, dayparts);

  return base::ReplaceStringPlaceholders(
      R"(
          INSERT INTO $1 (
            campaign_id,
            days_of_week,
            start_minute,
            end_minute
          ) VALUES $2)",
      {kTableName, BuildBindColumnPlaceholders(/*column_count=*/4, row_count)},
      nullptr);
}

}  // namespace

void InsertDayparts(
    const mojom::DBTransactionInfoPtr& mojom_db_transaction,
    const std::map</*campaign_id*/ std::string,
                   base::flat_set<CreativeDaypartInfo>>& dayparts) {
  CHECK(mojom_db_transaction);

  if (dayparts.empty()) {
    return;
  }

  mojom::DBActionInfoPtr mojom_db_action = mojom::DBActionInfo::New();
  mojom_db_action->type = mojom::DBActionInfo::Type::kExecuteWithBindings;
  mojom_db_action->sql = BuildInsertSql(mojom_db_action, dayparts);
  mojom_db_transaction->actions.push_back(std::move(mojom_db_action));
}

}  // namespace catsxp_ads::database::table
