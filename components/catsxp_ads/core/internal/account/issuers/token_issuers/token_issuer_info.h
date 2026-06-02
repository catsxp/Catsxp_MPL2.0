/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TOKEN_ISSUERS_TOKEN_ISSUER_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TOKEN_ISSUERS_TOKEN_ISSUER_INFO_H_

#include <string>
#include <vector>

#include "base/containers/flat_map.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_types.h"

namespace catsxp_ads {

using TokenIssuerPublicKeyMap =
    base::flat_map</*public_key*/ std::string, /*associated_value*/ double>;

struct TokenIssuerInfo final {
  TokenIssuerInfo();

  TokenIssuerInfo(const TokenIssuerInfo&);
  TokenIssuerInfo& operator=(const TokenIssuerInfo&);

  TokenIssuerInfo(TokenIssuerInfo&&) noexcept;
  TokenIssuerInfo& operator=(TokenIssuerInfo&&) noexcept;

  ~TokenIssuerInfo();

  bool operator==(const TokenIssuerInfo&) const = default;

  TokenIssuerType type = TokenIssuerType::kUndefined;
  TokenIssuerPublicKeyMap public_keys;
};

using TokenIssuerList = std::vector<TokenIssuerInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TOKEN_ISSUERS_TOKEN_ISSUER_INFO_H_
