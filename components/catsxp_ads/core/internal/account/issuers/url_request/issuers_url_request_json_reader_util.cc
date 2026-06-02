/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/url_request/issuers_url_request_json_reader_util.h"

#include <string_view>

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_value_util.h"

namespace catsxp_ads::json::reader {

namespace {

constexpr std::string_view kPingKey = "ping";
constexpr std::string_view kIssuersKey = "issuers";

}  // namespace

std::optional<int> ParsePing(const base::DictValue& dict) {
  return dict.FindInt(kPingKey);
}

std::optional<TokenIssuerList> ParseTokenIssuers(const base::DictValue& dict) {
  if (const auto* const list = dict.FindList(kIssuersKey)) {
    return MaybeBuildTokenIssuersFromList(*list);
  }

  return std::nullopt;
}

}  // namespace catsxp_ads::json::reader
