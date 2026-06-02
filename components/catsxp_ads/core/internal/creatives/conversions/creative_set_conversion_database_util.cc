/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_database_util.h"

#include "base/functional/bind.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_database_table.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"

namespace catsxp_ads::database {

void PurgeExpiredCreativeSetConversions() {
  const table::CreativeSetConversions database_table;
  database_table.PurgeExpired(base::BindOnce([](bool success) {
    if (!success) {
      return BLOG(0, "Failed to purge expired creative set conversions");
    }

    BLOG(3, "Successfully purged expired creative set conversions");
  }));
}

void SaveCreativeSetConversions(
    const CreativeSetConversionList& creative_set_conversions) {
  table::CreativeSetConversions database_table;
  database_table.Save(
      creative_set_conversions, base::BindOnce([](bool success) {
        if (!success) {
          return BLOG(0, "Failed to save creative set conversions");
        }

        BLOG(3, "Successfully saved creative set conversions");
      }));
}

}  // namespace catsxp_ads::database
