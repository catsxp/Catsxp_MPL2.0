/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_URL_REQUEST_ISSUERS_URL_REQUEST_JSON_READER_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_URL_REQUEST_ISSUERS_URL_REQUEST_JSON_READER_UTIL_H_

#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"

namespace base {
class DictValue;
}  // namespace base

namespace catsxp_ads::json::reader {

std::optional<int> ParsePing(const base::DictValue& dict);
std::optional<TokenIssuerList> ParseTokenIssuers(const base::DictValue& dict);

}  // namespace catsxp_ads::json::reader

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_URL_REQUEST_ISSUERS_URL_REQUEST_JSON_READER_UTIL_H_
