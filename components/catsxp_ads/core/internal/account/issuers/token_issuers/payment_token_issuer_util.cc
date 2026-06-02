/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/payment_token_issuer_util.h"

#include <optional>

#include "base/containers/flat_map.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_types.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_util.h"

namespace catsxp_ads {

bool IsPaymentTokenIssuerValid(const IssuersInfo& issuers) {
  std::optional<TokenIssuerInfo> payment_token_issuer =
      GetTokenIssuerForType(issuers, TokenIssuerType::kPayments);
  if (!payment_token_issuer) {
    return false;
  }

  const size_t maximum_token_issuer_public_keys =
      kMaximumTokenIssuerPublicKeys.Get();

  base::flat_map<double, size_t> buckets;
  for (const auto& [_, associated_value] : payment_token_issuer->public_keys) {
    ++buckets[associated_value];
    if (buckets[associated_value] > maximum_token_issuer_public_keys) {
      return false;
    }
  }

  return true;
}

}  // namespace catsxp_ads
