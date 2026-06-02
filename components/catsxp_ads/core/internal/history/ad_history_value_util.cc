/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_value_util.h"

#include <string_view>

#include "base/strings/string_number_conversions.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_value_util_internal.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_value_util.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kUuidKey = "uuid";
constexpr std::string_view kCreatedAtKey = "timestampInMilliseconds";
constexpr std::string_view kRowKey = "adDetailRows";

}  // namespace

base::ListValue AdHistoryToList(const AdHistoryList& ad_history) {
  base::ListValue list;
  list.reserve(ad_history.size());

  size_t row = 0;

  for (const auto& ad_history_item : ad_history) {
    list.Append(base::DictValue()
                    .Set(kUuidKey, base::NumberToString(row++))
                    .Set(kCreatedAtKey,
                         ad_history_item.created_at
                             .InMillisecondsFSinceUnixEpochIgnoringNull())
                    .Set(kRowKey, base::ListValue().Append(
                                      AdHistoryItemToDict(ad_history_item))));
  }

  return list;
}

}  // namespace catsxp_ads
