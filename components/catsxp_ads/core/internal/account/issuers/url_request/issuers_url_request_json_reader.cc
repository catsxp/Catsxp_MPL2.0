/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/url_request/issuers_url_request_json_reader.h"

#include "base/json/json_reader.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/url_request/issuers_url_request_json_reader_util.h"

namespace catsxp_ads::json::reader {

std::optional<IssuersInfo> ReadIssuers(const std::string& json) {
  std::optional<base::DictValue> dict =
      base::JSONReader::ReadDict(json, base::JSON_PARSE_RFC);
  if (!dict) {
    return std::nullopt;
  }

  std::optional<int> ping = ParsePing(*dict);
  if (!ping) {
    return std::nullopt;
  }

  std::optional<TokenIssuerList> token_issuers = ParseTokenIssuers(*dict);
  if (!token_issuers) {
    return std::nullopt;
  }

  IssuersInfo issuers;
  issuers.ping = *ping;
  issuers.token_issuers = *token_issuers;

  return issuers;
}

}  // namespace catsxp_ads::json::reader
