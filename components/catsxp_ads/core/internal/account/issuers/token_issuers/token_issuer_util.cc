/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_util.h"

#include <algorithm>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/confirmation_token_issuer_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/payment_token_issuer_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"

namespace catsxp_ads {

bool TokenIssuerExistsForType(TokenIssuerType token_issuer_type) {
  std::optional<IssuersInfo> issuers = GetIssuers();
  if (!issuers) {
    return false;
  }

  return !!GetTokenIssuerForType(*issuers, token_issuer_type);
}

std::optional<TokenIssuerInfo> GetTokenIssuerForType(
    const IssuersInfo& issuers,
    TokenIssuerType token_issuer_type) {
  const auto iter = std::ranges::find(issuers.token_issuers, token_issuer_type,
                                      &TokenIssuerInfo::type);
  if (iter == issuers.token_issuers.cend()) {
    return std::nullopt;
  }

  return *iter;
}

bool TokenIssuerPublicKeyExistsForType(TokenIssuerType token_issuer_type,
                                       const cbr::PublicKey& public_key) {
  std::optional<IssuersInfo> issuers = GetIssuers();
  if (!issuers) {
    return false;
  }

  std::optional<TokenIssuerInfo> token_issuer =
      GetTokenIssuerForType(*issuers, token_issuer_type);
  if (!token_issuer) {
    return false;
  }

  std::optional<std::string> public_key_base64 = public_key.EncodeBase64();

  return public_key_base64 &&
         token_issuer->public_keys.contains(public_key_base64);
}

}  // namespace catsxp_ads
