/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CLIENT_LEGACY_CLIENT_MIGRATION_AD_HISTORY_JSON_READER_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CLIENT_LEGACY_CLIENT_MIGRATION_AD_HISTORY_JSON_READER_UTIL_H_

#include <optional>

#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

namespace base {
class DictValue;
}  // namespace base

namespace catsxp_ads::json::reader {

std::optional<AdHistoryList> ParseAdHistory(const base::DictValue& dict);

}  // namespace catsxp_ads::json::reader

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CLIENT_LEGACY_CLIENT_MIGRATION_AD_HISTORY_JSON_READER_UTIL_H_
