/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/legacy_migration/client/legacy_client_migration_ad_history_json_reader.h"

#include "base/json/json_reader.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/legacy_migration/client/legacy_client_migration_ad_history_json_reader_util.h"

namespace catsxp_ads::json::reader {

std::optional<AdHistoryList> ReadAdHistory(const std::string& json) {
  std::optional<base::DictValue> dict =
      base::JSONReader::ReadDict(json, base::JSON_PARSE_RFC);
  if (!dict) {
    return std::nullopt;
  }

  return ParseAdHistory(*dict);
}

}  // namespace catsxp_ads::json::reader
