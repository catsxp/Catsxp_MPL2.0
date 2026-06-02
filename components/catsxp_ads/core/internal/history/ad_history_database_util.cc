/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_database_util.h"

#include "base/functional/bind.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_database_table.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

namespace catsxp_ads::database {

void PurgeExpiredAdHistory() {
  const table::AdHistory database_table;
  database_table.PurgeExpired(base::BindOnce([](bool success) {
    if (!success) {
      return BLOG(0, "Failed to purge expired ad history");
    }

    BLOG(3, "Successfully purged expired ad history");
  }));
}

void SaveAdHistory(const AdHistoryList& ad_history) {
  table::AdHistory database_table;
  database_table.Save(ad_history, base::BindOnce([](bool success) {
                        if (!success) {
                          return BLOG(0, "Failed to save ad history");
                        }

                        BLOG(3, "Successfully saved ad history");
                      }));
}

}  // namespace catsxp_ads::database
