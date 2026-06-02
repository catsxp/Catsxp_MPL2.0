/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKEN_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKEN_INFO_H_

#include <string>
#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"

namespace catsxp_ads {

struct ConfirmationTokenInfo final {
  bool operator==(const ConfirmationTokenInfo&) const = default;

  // Returns true if all cryptographic fields have valid values.
  [[nodiscard]] bool IsValid() const;

  cbr::UnblindedToken unblinded_token;
  cbr::PublicKey public_key;
  std::string signature_base64;
};

using ConfirmationTokenList = std::vector<ConfirmationTokenInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKEN_INFO_H_
