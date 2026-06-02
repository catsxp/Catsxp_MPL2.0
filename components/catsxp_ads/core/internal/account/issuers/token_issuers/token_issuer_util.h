/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TOKEN_ISSUERS_TOKEN_ISSUER_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TOKEN_ISSUERS_TOKEN_ISSUER_UTIL_H_

#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_types.h"

namespace catsxp_ads {

struct IssuersInfo;
struct TokenIssuerInfo;

namespace cbr {
class PublicKey;
}  // namespace cbr

bool TokenIssuerExistsForType(TokenIssuerType token_issuer_type);

std::optional<TokenIssuerInfo> GetTokenIssuerForType(
    const IssuersInfo& issuers,
    TokenIssuerType token_issuer_type);

bool TokenIssuerPublicKeyExistsForType(TokenIssuerType token_issuer_type,
                                       const cbr::PublicKey& public_key);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TOKEN_ISSUERS_TOKEN_ISSUER_UTIL_H_
