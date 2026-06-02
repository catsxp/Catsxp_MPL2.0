/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/legacy_migration/client/legacy_client_migration_ad_history_json_reader_util.h"

#include <string_view>

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_value_util.h"

namespace catsxp_ads::json::reader {

namespace {
constexpr std::string_view kAdHistoryKey = "adsShownHistory";
}  // namespace

std::optional<AdHistoryList> ParseAdHistory(const base::DictValue& dict) {
  const auto* const list = dict.FindList(kAdHistoryKey);
  if (!list) {
    return std::nullopt;
  }

  AdHistoryList ad_history;
  ad_history.reserve(list->size());

  for (const auto& value : *list) {
    if (const auto* const ad_history_item = value.GetIfDict()) {
      ad_history.push_back(AdHistoryItemFromDict(*ad_history_item));
    }
  }

  return ad_history;
}

}  // namespace catsxp_ads::json::reader
