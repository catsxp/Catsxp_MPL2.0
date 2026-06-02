/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/confirmation_token_issuer_util.h"

#include <cstddef>
#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_types.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_util.h"

namespace catsxp_ads {

bool IsConfirmationTokenIssuerValid(const IssuersInfo& issuers) {
  std::optional<TokenIssuerInfo> token_issuer =
      GetTokenIssuerForType(issuers, TokenIssuerType::kConfirmations);
  if (!token_issuer) {
    return false;
  }

  return token_issuer->public_keys.size() <=
         kMaximumTokenIssuerPublicKeys.Get();
}

}  // namespace catsxp_ads
